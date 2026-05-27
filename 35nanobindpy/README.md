# 35nanobindpy

The smallest useful nanobind example in this repo: a C++ `TenantManager`
class is exposed to Python as the `tenant_py` extension module.

## Files

- `csrc/tenant_py.cpp`: C++ class and nanobind bindings.
- `CMakeLists.txt`: builds the `tenant_py` Python extension.
- `pyproject.toml`: tells `pip` to build with `scikit-build-core`.
- `main.py`: imports and uses the compiled extension.

## Build and run

```bash
cd 35nanobindpy
uv sync
uv run python main.py
```

Expected output:

```text
Alice (30)
Bob (25)
```
