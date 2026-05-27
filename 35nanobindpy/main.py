def main():
    from tenant_py import TenantManager

    manager = TenantManager()
    manager.add_tenant("Alice", 30)
    manager.add_tenant("Bob", 25)

    print(manager.get_tenants(), end="")


if __name__ == "__main__":
    main()
