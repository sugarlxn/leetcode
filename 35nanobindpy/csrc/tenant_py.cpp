#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <string>
#include <vector>

namespace nb = nanobind;

// 一个简单的data class
struct Tenant {
    std::string name;
    int age;
};

class TenantManager {
public:
    void add_tenant(const std::string& name, int age) {
        tenants.emplace_back(Tenant{name, age});
    }

    std::string get_tenants() const {
        std::string result;
        for (const auto& tenant : tenants) {
            result += tenant.name + " (" + std::to_string(tenant.age) + ")\n";
        }
        return result;
    }
private:
    std::vector<Tenant> tenants;    
};

NB_MODULE(tenant_py, m) {
    m.doc() = "A simple Tenant Manager module";

    nb::class_<TenantManager>(m, "TenantManager")
        .def(nb::init<>())
        .def("add_tenant", &TenantManager::add_tenant, nb::arg("name"), nb::arg("age"))
        .def("get_tenants", &TenantManager::get_tenants);
}
