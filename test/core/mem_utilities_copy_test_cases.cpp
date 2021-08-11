#include "../skeleton.hpp"
#include "../userdata.hpp"
#include "../../core/mem_utilities.hpp"

namespace {
    using namespace glx;
    using namespace glx::mem;

    
    void glx_mem_copy_of_range_case1_not_overlapping() {
        UserData* arr = allocate<UserData>(128);
        for (auto offset = 0; offset < 128; offset++) {
            char str[128] = { 0 };
            snprintf(str, 128, "hello, world! %d", offset);
            construct(arr + offset, offset, offset * 10, offset * 100, str);
        }
        
        copy_of_range(arr, 0, 64, 64);
        
        for (auto offset = 0; offset < 64; offset++) {
            UserData& userData = arr[offset];
            Assertion::assert_is_equals(userData.i32, 64 + offset);
            Assertion::assert_is_equals(userData.f32, (64 + offset) * 10);
            Assertion::assert_is_equals(userData.f64, (64 + offset) * 100);
        }

        for (auto offset = 0; offset < 128; offset++) {
            destruct(arr + offset);
        }
        deallocate(arr);
    }

    void glx_mem_copy_of_range_case2_left_overlaping() {
        UserData* arr = allocate<UserData>(128);
        for (auto offset = 0; offset < 128; offset++) {
            char str[128] = { 0 };
            snprintf(str, 128, "hello, world! %d", offset);
            construct(arr + offset, offset, offset * 10, offset * 100, str);
        }

        copy_of_range(arr, 20, 0, 108);

        for (auto offset = 0; offset < 108; offset++) {
            UserData& userData = arr[20 + offset];
            Assertion::assert_is_equals(userData.i32, offset);
            Assertion::assert_is_equals(userData.f32, offset * 10);
            Assertion::assert_is_equals(userData.f64, offset * 100);
        }

        for (auto offset = 0; offset < 128; offset++) {
            destruct(arr + offset);
        }
        deallocate(arr);
    }

    void glx_mem_copy_of_range_case3_right_overlaping() {
        UserData* arr = allocate<UserData>(128);
        for (auto offset = 0; offset < 128; offset++) {
            char str[128] = { 0 };
            snprintf(str, 128, "hello, world! %d", offset);
            construct(arr + offset, offset, offset * 10, offset * 100, str);
        }

        copy_of_range(arr, 0, 20, 108);

        for (auto offset = 0; offset < 108; offset++) {
            UserData& userData = arr[offset];
            Assertion::assert_is_equals(userData.i32, 20 + offset);
            Assertion::assert_is_equals(userData.f32, (20 + offset) * 10);
            Assertion::assert_is_equals(userData.f64, (20 + offset) * 100);
        }

        for (auto offset = 0; offset < 128; offset++) {
            destruct(arr + offset);
        }
        deallocate(arr);
    }
}

int main(int argc, char *argv[]) {
    glx_mem_copy_of_range_case1_not_overlapping();
    glx_mem_copy_of_range_case2_left_overlaping();
    return 0;
}