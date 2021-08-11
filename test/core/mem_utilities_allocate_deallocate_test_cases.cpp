#include "../skeleton.hpp"
#include "../userdata.hpp"
#include "../../core/mem_utilities.hpp"

namespace {
    using namespace glx;
    using namespace glx::mem;

    void Glx_Mem_Allocate_Deallocate_Case1_IsNotNullptr() noexcept {
        using namespace mem;
        auto ptr = Allocate<UserData>(128);
        Assertion::AssertIsNotNullptr(ptr);
        Deallocate(ptr);
    }

    void Glx_Mem_Allocate_Deallocate_Case2_RandomAccess() noexcept {
        using namespace mem;
        auto ptr = Allocate<UserData>(128);
        for (auto offset = 0; offset < 128; offset++) {
            char str[128] = { 0 };
            snprintf(str, 128, "hello, world! %d", offset);
            new (ptr + offset) UserData(offset, offset * 10, offset * 100, str);
            auto value  = ptr[offset];
            auto i32 = value.i32;
            auto f32 = value.f32;
            auto f64 = value.f64;
            auto ptr1 = value.bytes;
            auto ptr2 = value.ptr;
            Assertion::AssertIsEquals(i32, value.i32);
            Assertion::AssertIsEquals(f32, value.f32);
            Assertion::AssertIsEquals(f64, value.f64);
            Assertion::AssertIsEquals(0, strncmp(value.bytes, ptr1, 128));
            Assertion::AssertIsEquals(0, memcmp(value.ptr, ptr2, 128));
        }
        for (auto offset = 1; offset < 128; offset++) {
            ptr[offset - 1] = ptr[offset];
        }
        for (auto offset = 1; offset < 128; offset++) {
            ptr[offset] = std::move(ptr[offset - 1]);
        }
        for (auto offset = 0; offset < 128; offset++) {
            auto object = reinterpret_cast<UserData*>(ptr + offset);
            object->~UserData();
        }
        Deallocate(ptr);
    }
}

int main(int argc, char *argv[]) {
    Glx_Mem_Allocate_Deallocate_Case1_IsNotNullptr();
    Glx_Mem_Allocate_Deallocate_Case2_RandomAccess();
    return 0;
}