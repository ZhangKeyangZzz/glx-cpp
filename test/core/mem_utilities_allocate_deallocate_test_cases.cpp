#include "../skeleton.hpp"
#include "../userdata.hpp"
#include "../../core/mem_utilities.hpp"

namespace {
    using namespace glx;
    using namespace glx::mem;

    void glx_mem_allocate_deallocate_case1_is_not_nullptr() noexcept {
        using namespace mem;
        auto ptr = allocate<UserData>(128);
        Assertion::assert_is_not_nullptr(ptr);
        deallocate(ptr);
    }

    void glx_mem_allocate_deallocate_case2_random_access() noexcept {
        using namespace mem;
        auto ptr = allocate<UserData>(128);
        for (auto offset = 0; offset < 128; offset++) {
            char str[128] = { 0 };
            snprintf(str, 128, "hello, world! %d", offset);
            construct(ptr + offset, offset, offset * 10, offset * 100, str);
            auto value  = ptr[offset];
            auto i32 = value.i32;
            auto f32 = value.f32;
            auto f64 = value.f64;
            auto ptr1 = value.bytes;
            auto ptr2 = value.ptr;
            Assertion::assert_is_equals(i32, value.i32);
            Assertion::assert_is_equals(f32, value.f32);
            Assertion::assert_is_equals(f64, value.f64);
            Assertion::assert_is_equals(0, strncmp(value.bytes, ptr1, 128));
            Assertion::assert_is_equals(0, memcmp(value.ptr, ptr2, 128));
        }
        for (auto offset = 1; offset < 128; offset++) {
            ptr[offset - 1] = ptr[offset];
        }
        for (auto offset = 1; offset < 128; offset++) {
            ptr[offset] = std::move(ptr[offset - 1]);
        }
        for (auto offset = 0; offset < 128; offset++) {
            destruct(ptr + offset);
        }
        deallocate(ptr);
    }
}

int main(int argc, char *argv[]) {
    glx_mem_allocate_deallocate_case1_is_not_nullptr();
    glx_mem_allocate_deallocate_case2_random_access();
    return 0;
}