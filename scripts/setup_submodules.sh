#!/usr/bin/env bash
set -euo pipefail

# Initialize and update submodules shallowly and with blob-less filter
git submodule init
git -c submodule.recurse=false submodule update --depth 1 --filter=blob:none --init

# Ensure inav submodule is configured for partial clone and sparse checkout
INAV_PATH="src/external/inav"
if [ -f "$INAV_PATH/.git" ] || [ -d "$INAV_PATH/.git" ] || git ls-files --stage | grep -q "160000\s\S\+\s$INAV_PATH$"; then
  # Enable partial clone settings (promisor and filter) inside the submodule
  git -C "$INAV_PATH" config remote.origin.promisor true || true
  git -C "$INAV_PATH" config remote.origin.partialclonefilter blob:none || true
  git -C "$INAV_PATH" config core.sparseCheckout true || true

  # Prefer modern sparse-checkout commands if available
  if git -C "$INAV_PATH" sparse-checkout -h >/dev/null 2>&1; then
    # Use no-cone to allow exact path
    git -C "$INAV_PATH" sparse-checkout init --no-cone || true
    git -C "$INAV_PATH" sparse-checkout set src/main/msp || true
  else
    # Fallback: write sparse-checkout file directly
    printf "src/main/msp/\n" > "$INAV_PATH/.git/info/sparse-checkout"
  fi

  # Determine the submodule commit pinned by the superproject, if any
  TARGET_SHA=$(git rev-parse HEAD 2>/dev/null >/dev/null && git ls-tree HEAD "$INAV_PATH" 2>/dev/null | awk '{print $3}') || true

  # Fetch the target commit shallowly or fallback to master
  if [ -n "${TARGET_SHA:-}" ]; then
    git -C "$INAV_PATH" fetch --depth=1 --filter=blob:none origin "$TARGET_SHA" || true
    # If the exact commit wasn't fetched (e.g. GC/pruned), fallback to branch
    if ! git -C "$INAV_PATH" cat-file -e "$TARGET_SHA^{commit}" 2>/dev/null; then
      git -C "$INAV_PATH" fetch --depth=1 --filter=blob:none origin master || true
      TARGET_SHA=FETCH_HEAD
    fi
    git -C "$INAV_PATH" checkout -f "$TARGET_SHA" || git -C "$INAV_PATH" checkout -f FETCH_HEAD
  else
    git -C "$INAV_PATH" fetch --depth=1 --filter=blob:none origin master || true
    git -C "$INAV_PATH" checkout -f FETCH_HEAD || true
  fi

  # Reapply sparse patterns (noop if already active)
  if git -C "$INAV_PATH" sparse-checkout -h >/dev/null 2>&1; then
    git -C "$INAV_PATH" sparse-checkout reapply || true
  fi
fi

echo "Submodules initialized. inav is sparsely checked out (src/main/msp only)."
