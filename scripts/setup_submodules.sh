#!/usr/bin/env bash
set -euo pipefail

# Initialize and update submodules shallowly and with blob-less filter
git submodule init
git -c submodule.recurse=false submodule update --depth 1 --filter=blob:none --init

# Ensure inav submodule is configured for partial clone and sparse checkout
INAV_PATH="src/external/inav"
if [ -d "$INAV_PATH/.git" ] || git ls-files --stage | grep -q "160000\s\S\+\s$INAV_PATH$"; then
  # Enable partial clone settings (promisor and filter) inside the submodule
  git -C "$INAV_PATH" config remote.origin.promisor true || true
  git -C "$INAV_PATH" config remote.origin.partialclonefilter blob:none || true
  git -C "$INAV_PATH" config core.sparseCheckout true || true
  printf "src/main/msp/\n" > "$INAV_PATH/.git/info/sparse-checkout"
  # Fetch minimal and checkout master tip (detached) respecting sparse patterns
  git -C "$INAV_PATH" fetch --depth=1 --filter=blob:none origin master
  git -C "$INAV_PATH" checkout -f FETCH_HEAD
fi

echo "Submodules initialized. inav is sparsely checked out (src/main/msp only)."
