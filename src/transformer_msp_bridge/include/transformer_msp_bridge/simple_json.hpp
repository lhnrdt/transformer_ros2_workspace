#pragma once

#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <istream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

namespace transformer_msp_bridge::simple_json
{

  class Value;

  using Array = std::vector<Value>;
  using Object = std::map<std::string, Value>;

  class Value
  {
  public:
    using Storage = std::variant<std::nullptr_t, bool, double, std::string, Array, Object>;

    Value() : data_(nullptr) {}
    explicit Value(bool b) : data_(b) {}
    explicit Value(double d) : data_(d) {}
    explicit Value(std::string s) : data_(std::move(s)) {}
    explicit Value(Array a) : data_(std::move(a)) {}
    explicit Value(Object o) : data_(std::move(o)) {}

    bool is_null() const { return std::holds_alternative<std::nullptr_t>(data_); }
    bool is_bool() const { return std::holds_alternative<bool>(data_); }
    bool is_number() const { return std::holds_alternative<double>(data_); }
    bool is_string() const { return std::holds_alternative<std::string>(data_); }
    bool is_array() const { return std::holds_alternative<Array>(data_); }
    bool is_object() const { return std::holds_alternative<Object>(data_); }

    bool as_bool() const
    {
      if (!is_bool())
        throw std::runtime_error("JSON value is not a boolean");
      return std::get<bool>(data_);
    }

    double as_number() const
    {
      if (!is_number())
        throw std::runtime_error("JSON value is not numeric");
      return std::get<double>(data_);
    }

    const std::string &as_string() const
    {
      if (!is_string())
        throw std::runtime_error("JSON value is not a string");
      return std::get<std::string>(data_);
    }

    const Array &as_array() const
    {
      if (!is_array())
        throw std::runtime_error("JSON value is not an array");
      return std::get<Array>(data_);
    }

    const Object &as_object() const
    {
      if (!is_object())
        throw std::runtime_error("JSON value is not an object");
      return std::get<Object>(data_);
    }

    const Value *find(const std::string &key) const
    {
      if (!is_object())
        return nullptr;
      const auto &obj = std::get<Object>(data_);
      auto it = obj.find(key);
      if (it == obj.end())
        return nullptr;
      return &it->second;
    }

    const Value &at(const std::string &key) const
    {
      if (!is_object())
        throw std::runtime_error("JSON value is not an object");
      const auto &obj = std::get<Object>(data_);
      auto it = obj.find(key);
      if (it == obj.end())
        throw std::runtime_error("JSON object missing key: " + key);
      return it->second;
    }

  private:
    Storage data_;
  };

  class Parser
  {
  public:
    explicit Parser(std::string_view text) : text_(text), pos_(0) {}

    Value parse()
    {
      skip_ws();
      Value result = parse_value();
      skip_ws();
      if (pos_ != text_.size())
        throw std::runtime_error("Unexpected trailing characters in JSON");
      return result;
    }

  private:
    std::string_view text_;
    std::size_t pos_;

    void skip_ws()
    {
      while (pos_ < text_.size() && std::isspace(static_cast<unsigned char>(text_[pos_])))
        ++pos_;
    }

    char peek() const
    {
      if (pos_ >= text_.size())
        throw std::runtime_error("Unexpected end of JSON input");
      return text_[pos_];
    }

    char get()
    {
      char ch = peek();
      ++pos_;
      return ch;
    }

    bool match(char expected)
    {
      if (pos_ < text_.size() && text_[pos_] == expected)
      {
        ++pos_;
        return true;
      }
      return false;
    }

    Value parse_value()
    {
      if (pos_ >= text_.size())
        throw std::runtime_error("Unexpected end of JSON input");
      char ch = text_[pos_];
      switch (ch)
      {
      case 'n':
        return parse_null();
      case 't':
        return parse_true();
      case 'f':
        return parse_false();
      case '"':
        return Value(parse_string());
      case '[':
        return Value(parse_array());
      case '{':
        return Value(parse_object());
      default:
        if (ch == '-' || std::isdigit(static_cast<unsigned char>(ch)))
          return Value(parse_number());
        break;
      }
      throw std::runtime_error("Invalid JSON value");
    }

    Value parse_null()
    {
      expect_literal("null");
      return Value();
    }

    Value parse_true()
    {
      expect_literal("true");
      return Value(true);
    }

    Value parse_false()
    {
      expect_literal("false");
      return Value(false);
    }

    std::string parse_string()
    {
      if (!match('"'))
        throw std::runtime_error("JSON string must begin with \"");
      std::string out;
      while (true)
      {
        if (pos_ >= text_.size())
          throw std::runtime_error("Unterminated JSON string");
        char ch = get();
        if (ch == '"')
          break;
        if (ch == '\\')
        {
          if (pos_ >= text_.size())
            throw std::runtime_error("Invalid escape in JSON string");
          char esc = get();
          switch (esc)
          {
          case '"': out.push_back('"'); break;
          case '\\': out.push_back('\\'); break;
          case '/': out.push_back('/'); break;
          case 'b': out.push_back('\b'); break;
          case 'f': out.push_back('\f'); break;
          case 'n': out.push_back('\n'); break;
          case 'r': out.push_back('\r'); break;
          case 't': out.push_back('\t'); break;
          case 'u':
            out += parse_unicode_escape();
            break;
          default:
            throw std::runtime_error("Invalid escape in JSON string");
          }
        }
        else
        {
          out.push_back(ch);
        }
      }
      return out;
    }

    std::string parse_unicode_escape()
    {
      auto parse_hex = [this]() -> uint32_t
      {
        if (pos_ + 4 > text_.size())
          throw std::runtime_error("Incomplete unicode escape");
        uint32_t value = 0;
        for (int i = 0; i < 4; ++i)
        {
          char ch = text_[pos_ + i];
          value <<= 4;
          if (ch >= '0' && ch <= '9')
            value |= static_cast<uint32_t>(ch - '0');
          else if (ch >= 'a' && ch <= 'f')
            value |= static_cast<uint32_t>(10 + ch - 'a');
          else if (ch >= 'A' && ch <= 'F')
            value |= static_cast<uint32_t>(10 + ch - 'A');
          else
            throw std::runtime_error("Invalid hex digit in unicode escape");
        }
        pos_ += 4;
        return value;
      };

      uint32_t code_unit = parse_hex();
      uint32_t codepoint = code_unit;

      if (code_unit >= 0xD800 && code_unit <= 0xDBFF)
      {
        // high surrogate, expect second \u
        if (!(match('\\') && match('u')))
          throw std::runtime_error("Invalid unicode surrogate pair");
        uint32_t low = parse_hex();
        if (low < 0xDC00 || low > 0xDFFF)
          throw std::runtime_error("Invalid unicode surrogate pair");
        codepoint = 0x10000 + ((code_unit - 0xD800) << 10) + (low - 0xDC00);
      }

      std::string utf8;
      if (codepoint <= 0x7F)
      {
        utf8.push_back(static_cast<char>(codepoint));
      }
      else if (codepoint <= 0x7FF)
      {
        utf8.push_back(static_cast<char>(0xC0 | ((codepoint >> 6) & 0x1F)));
        utf8.push_back(static_cast<char>(0x80 | (codepoint & 0x3F)));
      }
      else if (codepoint <= 0xFFFF)
      {
        utf8.push_back(static_cast<char>(0xE0 | ((codepoint >> 12) & 0x0F)));
        utf8.push_back(static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)));
        utf8.push_back(static_cast<char>(0x80 | (codepoint & 0x3F)));
      }
      else if (codepoint <= 0x10FFFF)
      {
        utf8.push_back(static_cast<char>(0xF0 | ((codepoint >> 18) & 0x07)));
        utf8.push_back(static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F)));
        utf8.push_back(static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)));
        utf8.push_back(static_cast<char>(0x80 | (codepoint & 0x3F)));
      }
      else
      {
        throw std::runtime_error("Unicode codepoint out of range");
      }
      return utf8;
    }

    double parse_number()
    {
      std::size_t start = pos_;
      if (match('-'))
      {
        // nothing else
      }
      if (match('0'))
      {
        // single zero
      }
      else
      {
        if (!std::isdigit(static_cast<unsigned char>(peek())))
          throw std::runtime_error("Invalid number");
        while (pos_ < text_.size() && std::isdigit(static_cast<unsigned char>(text_[pos_])))
          ++pos_;
      }
      if (match('.'))
      {
        if (pos_ >= text_.size() || !std::isdigit(static_cast<unsigned char>(text_[pos_])))
          throw std::runtime_error("Invalid fractional part");
        while (pos_ < text_.size() && std::isdigit(static_cast<unsigned char>(text_[pos_])))
          ++pos_;
      }
      if (pos_ < text_.size() && (text_[pos_] == 'e' || text_[pos_] == 'E'))
      {
        ++pos_;
        if (pos_ < text_.size() && (text_[pos_] == '+' || text_[pos_] == '-'))
          ++pos_;
        if (pos_ >= text_.size() || !std::isdigit(static_cast<unsigned char>(text_[pos_])))
          throw std::runtime_error("Invalid exponent");
        while (pos_ < text_.size() && std::isdigit(static_cast<unsigned char>(text_[pos_])))
          ++pos_;
      }

      const std::string slice(text_.substr(start, pos_ - start));
      char *end_ptr = nullptr;
      const double value = std::strtod(slice.c_str(), &end_ptr);
      if (end_ptr != slice.c_str() + slice.size())
        throw std::runtime_error("Failed to convert number");
      return value;
    }

    Array parse_array()
    {
      if (!match('['))
        throw std::runtime_error("JSON array must begin with [");
      Array arr;
      skip_ws();
      if (match(']'))
        return arr;
      while (true)
      {
        arr.push_back(parse_value());
        skip_ws();
        if (match(']'))
          break;
        if (!match(','))
          throw std::runtime_error("Expected ',' in array");
        skip_ws();
      }
      return arr;
    }

    Object parse_object()
    {
      if (!match('{'))
        throw std::runtime_error("JSON object must begin with {");
      Object obj;
      skip_ws();
      if (match('}'))
        return obj;
      while (true)
      {
        skip_ws();
        std::string key = parse_string();
        skip_ws();
        if (!match(':'))
          throw std::runtime_error("Expected ':' after key in object");
        skip_ws();
        obj.emplace(std::move(key), parse_value());
        skip_ws();
        if (match('}'))
          break;
        if (!match(','))
          throw std::runtime_error("Expected ',' in object");
        skip_ws();
      }
      return obj;
    }

    void expect_literal(const char *literal)
    {
      const char *p = literal;
      while (*p)
      {
        if (pos_ >= text_.size() || text_[pos_] != *p)
          throw std::runtime_error("Unexpected literal in JSON");
        ++pos_;
        ++p;
      }
    }
  };

  inline Value parse(std::string_view text)
  {
    Parser parser(text);
    return parser.parse();
  }

  inline Value parse_stream(std::istream &stream)
  {
    std::ostringstream oss;
    oss << stream.rdbuf();
    return parse(oss.str());
  }

  inline Value parse_file(const std::string &path)
  {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file)
      throw std::runtime_error("Unable to open JSON file: " + path);
    return parse_stream(file);
  }

} // namespace transformer_msp_bridge::simple_json
