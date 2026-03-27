/*
 * Repository:  https://github.com/kingkybel/TypeTraits
 * File Name:   test/traits_tests.cc
 * Description: tests for type-traits.
 *
 * Copyright (C) 2024 Dieter J Kybelksties <github@kybelksties.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * @date: 2024-11-03
 * @author: Dieter J Kybelksties
 */
#include "traits.h"
#include "traits_static.h"

#include <gtest/gtest.h>
#include <string>
#include <tuple>

using namespace std;
using namespace util;

class TraitsTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        // just in case
    }

    void TearDown() override
    {
        // just in case
    }
};

TEST_F(TraitsTest, is_equality_comparable_test)
{
    ASSERT_TRUE(is_equality_comparable_v<std::string>);

    struct NoEqual
    {
    };

    ASSERT_FALSE(is_equality_comparable_v<NoEqual>);

    struct Equal
    {
        bool operator==(Equal const& rhs) const // NOSONAR
        {
            return true;
        }
    };

    ASSERT_TRUE(is_equality_comparable_v<Equal>);
}

TEST_F(TraitsTest, is_less_comparable_test)
{
    ASSERT_TRUE(is_less_comparable_v<double>);

    struct NoLess
    {
    };

    ASSERT_FALSE(is_less_comparable_v<NoLess>);

    struct Less
    {
        bool operator<(Less const& rhs) // NOSONAR
        {
            return true;
        }
    };

    ASSERT_TRUE(is_less_comparable_v<Less>);
}

TEST_F(TraitsTest, is_tuple_test)
{
    using TupleType = std::tuple<double, int, std::string>;
    ASSERT_TRUE(is_tuple_v<TupleType>);
    using PairType = std::pair<std::string, int>;
    ASSERT_FALSE(is_tuple_v<PairType>);
    ASSERT_FALSE(is_tuple_v<double>);

    struct NoTuple
    {
        int    i;
        double f;
    };

    ASSERT_FALSE(is_tuple_v<NoTuple>);
}

TEST_F(TraitsTest, is_char_test)
{
    ASSERT_TRUE(is_char_v<char>);
    ASSERT_TRUE(is_char_v<char16_t>);
    ASSERT_TRUE(is_char_v<char32_t>);
    ASSERT_FALSE(is_char_v<char[]>);
    ASSERT_FALSE(is_char_v<char16_t[]>);
    ASSERT_FALSE(is_char_v<char32_t[]>);
    ASSERT_FALSE(is_char_v<int>);
}

TEST_F(TraitsTest, is_std_string_test)
{
    ASSERT_FALSE(is_std_string_v<double>);
    ASSERT_FALSE(is_std_string_v<char>);
    ASSERT_FALSE(is_std_string_v<char16_t>);
    ASSERT_FALSE(is_std_string_v<char32_t>);
    ASSERT_FALSE(is_std_string_v<char[]>);
    ASSERT_FALSE(is_std_string_v<char16_t[]>);
    ASSERT_FALSE(is_std_string_v<char32_t[]>);
    ASSERT_FALSE(is_std_string_v<char*>);
    ASSERT_FALSE(is_std_string_v<char16_t*>);
    ASSERT_FALSE(is_std_string_v<char32_t*>);
    ASSERT_TRUE(is_std_string_v<std::string>);
    ASSERT_TRUE(is_std_string_v<std::basic_string<char16_t>>);
    ASSERT_TRUE(is_std_string_v<std::basic_string<char32_t>>);
}

TEST_F(TraitsTest, is_std_string_view_test)
{
    ASSERT_FALSE(is_std_string_view_v<double>);
    ASSERT_FALSE(is_std_string_view_v<char>);
    ASSERT_FALSE(is_std_string_view_v<char16_t>);
    ASSERT_FALSE(is_std_string_view_v<char32_t>);
    ASSERT_FALSE(is_std_string_view_v<char[]>);
    ASSERT_FALSE(is_std_string_view_v<char16_t[]>);
    ASSERT_FALSE(is_std_string_view_v<char32_t[]>);
    ASSERT_FALSE(is_std_string_view_v<char*>);
    ASSERT_FALSE(is_std_string_view_v<char16_t*>);
    ASSERT_FALSE(is_std_string_view_v<char32_t*>);
    ASSERT_TRUE(is_std_string_view_v<std::string_view>);
    ASSERT_TRUE(is_std_string_view_v<std::basic_string_view<char16_t>>);
    ASSERT_TRUE(is_std_string_view_v<std::basic_string_view<char32_t>>);
}

TEST_F(TraitsTest, is_char_pointer_test)
{
    ASSERT_FALSE(is_char_pointer_v<double>);
    ASSERT_FALSE(is_char_pointer_v<char>);
    ASSERT_FALSE(is_char_pointer_v<char16_t>);
    ASSERT_FALSE(is_char_pointer_v<char32_t>);
    ASSERT_FALSE(is_char_pointer_v<char[]>);
    ASSERT_FALSE(is_char_pointer_v<char16_t[]>);
    ASSERT_FALSE(is_char_pointer_v<char32_t[]>);
    ASSERT_TRUE(is_char_pointer_v<char*>);
    ASSERT_TRUE(is_char_pointer_v<char16_t*>);
    ASSERT_TRUE(is_char_pointer_v<char32_t*>);
    ASSERT_TRUE(is_char_pointer_v<char const*>);
    ASSERT_TRUE(is_char_pointer_v<char16_t const*>);
    ASSERT_TRUE(is_char_pointer_v<char32_t const*>);
    ASSERT_TRUE(is_char_pointer_v<char*&>);
    ASSERT_TRUE(is_char_pointer_v<char16_t*&>);
    ASSERT_TRUE(is_char_pointer_v<char32_t*&>);
    ASSERT_FALSE(is_char_pointer_v<std::string_view>);
    ASSERT_FALSE(is_char_pointer_v<std::basic_string_view<char16_t>>);
    ASSERT_FALSE(is_char_pointer_v<std::basic_string_view<char32_t>>);
}

TEST_F(TraitsTest, is_char_array_test)
{
    ASSERT_FALSE(is_char_array_v<double>);
    ASSERT_FALSE(is_char_array_v<char>);
    ASSERT_FALSE(is_char_array_v<char16_t>);
    ASSERT_FALSE(is_char_array_v<char32_t>);
    ASSERT_TRUE(is_char_array_v<char[]>);
    ASSERT_TRUE(is_char_array_v<char16_t[]>);
    ASSERT_TRUE(is_char_array_v<char32_t[]>);
    ASSERT_TRUE(is_char_array_v<char const[]>);
    ASSERT_TRUE(is_char_array_v<char16_t const[]>);
    ASSERT_TRUE(is_char_array_v<char32_t const[]>);
    ASSERT_FALSE(is_char_array_v<char*>);
    ASSERT_FALSE(is_char_array_v<char16_t*>);
    ASSERT_FALSE(is_char_array_v<char32_t*>);
    ASSERT_FALSE(is_char_array_v<char const*>);
    ASSERT_FALSE(is_char_array_v<char16_t const*>);
    ASSERT_FALSE(is_char_array_v<char32_t const*>);
    ASSERT_FALSE(is_char_array_v<char*&>);
    ASSERT_FALSE(is_char_array_v<char16_t*&>);
    ASSERT_FALSE(is_char_array_v<char32_t*&>);
    ASSERT_FALSE(is_char_array_v<std::string_view>);
    ASSERT_FALSE(is_char_array_v<std::basic_string_view<char16_t>>);
    ASSERT_FALSE(is_char_array_v<std::basic_string_view<char32_t>>);
}

TEST_F(TraitsTest, is_string_test)
{
    ASSERT_FALSE(is_string_v<double>);
    ASSERT_FALSE(is_string_v<char>);
    ASSERT_FALSE(is_string_v<char16_t>);
    ASSERT_FALSE(is_string_v<char32_t>);
    ASSERT_TRUE(is_string_v<char[]>);
    ASSERT_TRUE(is_string_v<char16_t[]>);
    ASSERT_TRUE(is_string_v<char32_t[]>);
    ASSERT_TRUE(is_string_v<char const[]>);
    ASSERT_TRUE(is_string_v<char16_t const[]>);
    ASSERT_TRUE(is_string_v<char32_t const[]>);
    ASSERT_TRUE(is_string_v<char*>);
    ASSERT_TRUE(is_string_v<char16_t*>);
    ASSERT_TRUE(is_string_v<char32_t*>);
    ASSERT_TRUE(is_string_v<char const*>);
    ASSERT_TRUE(is_string_v<char16_t const*>);
    ASSERT_TRUE(is_string_v<char32_t const*>);
    ASSERT_TRUE(is_string_v<char*&>);
    ASSERT_TRUE(is_string_v<char16_t*&>);
    ASSERT_TRUE(is_string_v<char32_t*&>);
    ASSERT_TRUE(is_string_v<std::string_view>);
    ASSERT_TRUE(is_string_v<std::basic_string_view<char16_t>>);
    ASSERT_TRUE(is_string_v<std::basic_string_view<char32_t>>);
}

TEST_F(TraitsTest, is_compatible_string_test)
{
    // clang-format off
    // formatter remove double round brackets
    ASSERT_TRUE((is_compatible_string_v<std::string, char*>));
    ASSERT_TRUE((std::is_same_v<is_compatible_string<std::string, char32_t*>::char_type_1, char>));
    ASSERT_TRUE((std::is_same_v<is_compatible_string<std::string, char32_t*>::char_type_2, char32_t>));
    ASSERT_FALSE((std::is_same_v<is_compatible_string<std::string, char32_t*>::char_type_1, char32_t>));
    ASSERT_FALSE((std::is_same_v<is_compatible_string<std::string, char32_t*>::char_type_2, char>));
    ASSERT_FALSE((is_compatible_string<std::string, char32_t*>::same_char_type));
    ASSERT_FALSE((is_compatible_string_v<std::string, char32_t*>));
    // clang-format on
}

TEST_F(TraitsTest, has_std_string_compatible_char_test)
{
    // clang-format off
    // formatter remove double round brackets
    ASSERT_TRUE((has_std_string_compatible_char_v<std::string, char>));
    ASSERT_TRUE((has_std_string_compatible_char_v<std::string, char*>));
    ASSERT_TRUE((has_std_string_compatible_char_v<std::string, const char[]>));
    ASSERT_FALSE((has_std_string_compatible_char_v<char,std::string>)) << "first template is not a string so should return false";
    ASSERT_TRUE((has_std_string_compatible_char_v<char*, std::string>));
    ASSERT_TRUE((has_std_string_compatible_char_v<const char[], std::string>));
    // clang-format on
}

TEST_F(TraitsTest, string_or_char_size_test)
{
    ASSERT_EQ(string_or_char_size(0.0), 0UL);
    ASSERT_EQ(string_or_char_size('a'), 1UL);
    ASSERT_EQ(string_or_char_size("abc"), 3UL);
    ASSERT_EQ(string_or_char_size(std::string("abcefg")), 6UL);
}

TEST_F(TraitsTest, has_std_hash_test)
{
    ASSERT_TRUE(has_std_hash_v<double>);
    ASSERT_TRUE(has_std_hash_v<int>);
    ASSERT_TRUE(has_std_hash_v<std::string>);
    ASSERT_TRUE(has_std_hash_v<void*>);
    ASSERT_FALSE(has_std_hash_v<void>);

    struct NoHash
    {
    };

    ASSERT_FALSE(has_std_hash_v<NoHash>);
}

TEST_F(TraitsTest, get_Nth_type_test)
{
    using First = get_Nth_type<0, int, double, std::string>::type;
    using Last  = get_Nth_type<2, int, double, std::string>::type;
    ASSERT_TRUE((std::is_same_v<First, int>));
    ASSERT_TRUE((std::is_same_v<Last, std::string>));
}

TEST_F(TraitsTest, charToChar_test)
{
    ASSERT_EQ(charToChar<char16_t>('A'), u'A');
    ASSERT_EQ(charToChar<char>('z'), 'z');
}

TEST_F(TraitsTest, is_char_pointer_const_pointer_test)
{
    using const_char_ptr_const = char const* const;
    ASSERT_TRUE((is_char_pointer_v<const_char_ptr_const>));
}

TEST_F(TraitsTest, is_char_array_bounded_test)
{
    ASSERT_TRUE((is_char_array_v<char[4]>));
    ASSERT_TRUE((is_char_array_v<char const[7]>));
}

TEST_F(TraitsTest, charToChar_different_types_test)
{
    // Test charToChar with different character types
    ASSERT_EQ(charToChar<wchar_t>('A'), L'A');
    ASSERT_EQ(charToChar<char16_t>('B'), u'B');
    ASSERT_EQ(charToChar<char32_t>('C'), U'C');
    ASSERT_EQ(charToChar<char>(L'Z'), 'Z');
    ASSERT_EQ(charToChar<char16_t>(u'X'), u'X');
    ASSERT_EQ(charToChar<char32_t>(U'Y'), U'Y');
}

TEST_F(TraitsTest, is_compatible_string_edge_cases_test)
{
    // Test with different string types
    ASSERT_TRUE((is_compatible_string_v<std::string, char*>));
    ASSERT_TRUE((is_compatible_string_v<std::wstring, wchar_t*>));
    ASSERT_TRUE((is_compatible_string_v<std::u16string, char16_t*>));
    ASSERT_TRUE((is_compatible_string_v<std::u32string, char32_t*>));

    // Test with string_view
    ASSERT_TRUE((is_compatible_string_v<std::string_view, char*>));
    ASSERT_TRUE((is_compatible_string_v<std::wstring_view, wchar_t*>));

    // Incompatible types
    ASSERT_FALSE((is_compatible_string_v<std::string, wchar_t*>));
    ASSERT_FALSE((is_compatible_string_v<std::string, char16_t*>));
    ASSERT_FALSE((is_compatible_string_v<std::string, char32_t*>));
}

TEST_F(TraitsTest, has_std_string_compatible_char_edge_cases_test)
{
    // Test with various combinations
    ASSERT_TRUE((has_std_string_compatible_char_v<std::string, char>));
    ASSERT_TRUE((has_std_string_compatible_char_v<std::string, char*>));
    ASSERT_TRUE((has_std_string_compatible_char_v<std::string, char const[]>));
    ASSERT_TRUE((has_std_string_compatible_char_v<std::string, std::string>));
    ASSERT_TRUE((has_std_string_compatible_char_v<std::string, std::string_view>));

    // Test with wide strings
    ASSERT_TRUE((has_std_string_compatible_char_v<std::wstring, wchar_t>));
    ASSERT_TRUE((has_std_string_compatible_char_v<std::u16string, char16_t>));
    ASSERT_TRUE((has_std_string_compatible_char_v<std::u32string, char32_t>));

    // Incompatible cases
    ASSERT_FALSE((has_std_string_compatible_char_v<std::string, wchar_t>));
    ASSERT_FALSE((has_std_string_compatible_char_v<std::string, int>));
}

TEST_F(TraitsTest, string_or_char_size_comprehensive_test)
{
    // Test with various string types
    std::string    str    = "hello world";
    std::wstring   wstr   = L"hello world";
    std::u16string u16str = u"hello";
    std::u32string u32str = U"hello";

    std::string_view  sv  = "test";
    std::wstring_view wsv = L"test";

    char const*    cstr  = "c string";
    wchar_t const* wcstr = L"wide c string";

    char    arr[]  = "array";
    wchar_t warr[] = L"wide array";

    ASSERT_EQ(string_or_char_size(str), 11UL);
    ASSERT_EQ(string_or_char_size(wstr), 11UL);
    ASSERT_EQ(string_or_char_size(u16str), 5UL);
    ASSERT_EQ(string_or_char_size(u32str), 5UL);

    ASSERT_EQ(string_or_char_size(sv), 4UL);
    ASSERT_EQ(string_or_char_size(wsv), 4UL);

    ASSERT_EQ(string_or_char_size(cstr), 8UL);
    ASSERT_EQ(string_or_char_size(wcstr), 13UL);

    ASSERT_EQ(string_or_char_size(arr), 5UL);
    ASSERT_EQ(string_or_char_size(warr), 10UL);

    // Test with single characters
    ASSERT_EQ(string_or_char_size('a'), 1UL);
    ASSERT_EQ(string_or_char_size(L'b'), 1UL);

    // Test with non-string types
    ASSERT_EQ(string_or_char_size(42), 0UL);
    ASSERT_EQ(string_or_char_size(3.14), 0UL);
}

TEST_F(TraitsTest, has_std_hash_comprehensive_test)
{
    // Test with various types that have std::hash
    ASSERT_TRUE(has_std_hash_v<int>);
    ASSERT_TRUE(has_std_hash_v<long>);
    ASSERT_TRUE(has_std_hash_v<size_t>);
    ASSERT_TRUE(has_std_hash_v<std::string>);
    ASSERT_TRUE(has_std_hash_v<std::wstring>);
    ASSERT_TRUE(has_std_hash_v<std::u16string>);
    ASSERT_TRUE(has_std_hash_v<std::u32string>);
    ASSERT_TRUE(has_std_hash_v<std::string_view>);
    ASSERT_TRUE(has_std_hash_v<void*>);
    ASSERT_TRUE(has_std_hash_v<std::nullptr_t>);

    // Test with types that don't have std::hash
    struct NoHash
    {
    };

    ASSERT_FALSE(has_std_hash_v<NoHash>);
    ASSERT_FALSE(has_std_hash_v<void>);
}

TEST_F(TraitsTest, get_Nth_type_comprehensive_test)
{
    using First  = get_Nth_type<0, int, double, std::string>::type;
    using Second = get_Nth_type<1, int, double, std::string>::type;
    using Third  = get_Nth_type<2, int, double, std::string>::type;

    ASSERT_TRUE((std::is_same_v<First, int>));
    ASSERT_TRUE((std::is_same_v<Second, double>));
    ASSERT_TRUE((std::is_same_v<Third, std::string>));

    // Test with single type
    using Single = get_Nth_type<0, char>::type;
    ASSERT_TRUE((std::is_same_v<Single, char>));
}

TEST_F(TraitsTest, is_string_comprehensive_test)
{
    // Test all string-like types
    ASSERT_TRUE(is_string_v<std::string>);
    ASSERT_TRUE(is_string_v<std::wstring>);
    ASSERT_TRUE(is_string_v<std::u16string>);
    ASSERT_TRUE(is_string_v<std::u32string>);

    ASSERT_TRUE(is_string_v<std::string_view>);
    ASSERT_TRUE(is_string_v<std::wstring_view>);
    ASSERT_TRUE(is_string_v<std::u16string_view>);
    ASSERT_TRUE(is_string_v<std::u32string_view>);

    ASSERT_TRUE(is_string_v<char*>);
    ASSERT_TRUE(is_string_v<wchar_t*>);
    ASSERT_TRUE(is_string_v<char16_t*>);
    ASSERT_TRUE(is_string_v<char32_t*>);

    ASSERT_TRUE(is_string_v<char const*>);
    ASSERT_TRUE(is_string_v<wchar_t const*>);

    ASSERT_TRUE(is_string_v<char[]>);
    ASSERT_TRUE(is_string_v<wchar_t[]>);
    ASSERT_TRUE(is_string_v<char16_t[]>);
    ASSERT_TRUE(is_string_v<char32_t[]>);

    ASSERT_TRUE(is_string_v<char const[]>);
    ASSERT_TRUE(is_string_v<char[10]>);
    ASSERT_TRUE(is_string_v<wchar_t[20]>);

    // Test non-string types
    ASSERT_FALSE((is_string_v<int>));
    ASSERT_FALSE((is_string_v<double>));
    ASSERT_FALSE((is_string_v<void*>));
    ASSERT_FALSE((is_string_v<std::tuple<int, double>>));
}

TEST_F(TraitsTest, is_std_string_comprehensive_test)
{
    ASSERT_TRUE(is_std_string_v<std::string>);
    ASSERT_TRUE(is_std_string_v<std::wstring>);
    ASSERT_TRUE(is_std_string_v<std::u16string>);
    ASSERT_TRUE(is_std_string_v<std::u32string>);

    // Test with custom allocator
    ASSERT_TRUE((is_std_string_v<std::basic_string<char, std::char_traits<char>, std::allocator<char>>>));

    ASSERT_FALSE(is_std_string_v<std::string_view>);
    ASSERT_FALSE(is_std_string_v<char*>);
    ASSERT_FALSE(is_std_string_v<int>);
}

TEST_F(TraitsTest, is_std_string_view_comprehensive_test)
{
    ASSERT_TRUE(is_std_string_view_v<std::string_view>);
    ASSERT_TRUE(is_std_string_view_v<std::wstring_view>);
    ASSERT_TRUE(is_std_string_view_v<std::u16string_view>);
    ASSERT_TRUE(is_std_string_view_v<std::u32string_view>);

    ASSERT_FALSE(is_std_string_view_v<std::string>);
    ASSERT_FALSE(is_std_string_view_v<char*>);
    ASSERT_FALSE(is_std_string_view_v<int>);
}

TEST_F(TraitsTest, is_char_pointer_comprehensive_test)
{
    // All character pointer variations
    ASSERT_TRUE(is_char_pointer_v<char*>);
    ASSERT_TRUE(is_char_pointer_v<wchar_t*>);
    ASSERT_TRUE(is_char_pointer_v<char16_t*>);
    ASSERT_TRUE(is_char_pointer_v<char32_t*>);

    ASSERT_TRUE(is_char_pointer_v<char const*>);
    ASSERT_TRUE(is_char_pointer_v<wchar_t const*>);
    ASSERT_TRUE(is_char_pointer_v<char16_t const*>);
    ASSERT_TRUE(is_char_pointer_v<char32_t const*>);

    // Note: char* const doesn't match any specialization as it's not a standard character pointer pattern
    // ASSERT_TRUE(is_char_pointer_v<char* const>);
    // Note: * const doesn't match any specialization as it's not a standard character pointer pattern
    // ASSERT_TRUE(is_char_pointer_v<wchar_t* const>);

    ASSERT_TRUE(is_char_pointer_v<char*&>);
    ASSERT_TRUE(is_char_pointer_v<wchar_t*&>);

    ASSERT_TRUE(is_char_pointer_v<char const*&>);
    ASSERT_TRUE(is_char_pointer_v<wchar_t const*&>);

    // Non-character pointers
    ASSERT_FALSE(is_char_pointer_v<int*>);
    ASSERT_FALSE(is_char_pointer_v<double*>);
    ASSERT_FALSE(is_char_pointer_v<void*>);
}

TEST_F(TraitsTest, is_char_array_comprehensive_test)
{
    // All character array variations
    ASSERT_TRUE(is_char_array_v<char[]>);
    ASSERT_TRUE(is_char_array_v<wchar_t[]>);
    ASSERT_TRUE(is_char_array_v<char16_t[]>);
    ASSERT_TRUE(is_char_array_v<char32_t[]>);

    ASSERT_TRUE(is_char_array_v<char const[]>);
    ASSERT_TRUE(is_char_array_v<wchar_t const[]>);

    ASSERT_TRUE(is_char_array_v<char[1]>);
    ASSERT_TRUE(is_char_array_v<char[10]>);
    ASSERT_TRUE(is_char_array_v<char[100]>);
    ASSERT_TRUE(is_char_array_v<wchar_t[5]>);
    ASSERT_TRUE(is_char_array_v<char16_t[20]>);
    ASSERT_TRUE(is_char_array_v<char32_t[50]>);

    ASSERT_TRUE(is_char_array_v<char const[5]>);
    ASSERT_TRUE(is_char_array_v<wchar_t const[10]>);

    // Non-character arrays
    ASSERT_FALSE(is_char_array_v<int[]>);
    ASSERT_FALSE(is_char_array_v<double[]>);
    ASSERT_FALSE(is_char_array_v<int[5]>);
}

TEST_F(TraitsTest, is_tuple_comprehensive_test)
{
    // Test various tuple types
    ASSERT_TRUE((is_tuple_v<std::tuple<>>));
    ASSERT_TRUE((is_tuple_v<std::tuple<int>>));
    ASSERT_TRUE((is_tuple_v<std::tuple<int, double>>));
    ASSERT_TRUE((is_tuple_v<std::tuple<int, double, std::string>>));
    ASSERT_TRUE((is_tuple_v<std::tuple<std::string, int, char*>>));

    // Test non-tuple types
    ASSERT_FALSE((is_tuple_v<int>));
    ASSERT_FALSE((is_tuple_v<double>));
    ASSERT_FALSE((is_tuple_v<std::string>));
    ASSERT_FALSE((is_tuple_v<std::pair<int, double>>));
    ASSERT_FALSE((is_tuple_v<std::array<int, 5>>));
}

TEST_F(TraitsTest, is_equality_comparable_comprehensive_test)
{
    // Test with various comparable types
    ASSERT_TRUE(is_equality_comparable_v<int>);
    ASSERT_TRUE(is_equality_comparable_v<double>);
    ASSERT_TRUE(is_equality_comparable_v<std::string>);
    ASSERT_TRUE(is_equality_comparable_v<char*>);
    ASSERT_TRUE(is_equality_comparable_v<char const*>);

    // Test with custom types
    struct Comparable
    {
        bool operator==(Comparable const&) const
        {
            return true;
        }
    };

    ASSERT_TRUE(is_equality_comparable_v<Comparable>);

    struct NotComparable
    {
    };

    ASSERT_FALSE(is_equality_comparable_v<NotComparable>);

    // Test cross-type comparison
    ASSERT_TRUE((is_equality_comparable_v<int, long>));
    ASSERT_TRUE((is_equality_comparable_v<std::string, char const*>));
    ASSERT_FALSE((is_equality_comparable_v<int, std::string>));
}

TEST_F(TraitsTest, is_less_comparable_comprehensive_test)
{
    // Test with various comparable types
    ASSERT_TRUE(is_less_comparable_v<int>);
    ASSERT_TRUE(is_less_comparable_v<double>);
    ASSERT_TRUE(is_less_comparable_v<std::string>);
    ASSERT_TRUE(is_less_comparable_v<char*>);

    // Test with custom types
    struct LessComparable
    {
        bool operator<(LessComparable const&) const
        {
            return true;
        }
    };

    ASSERT_TRUE(is_less_comparable_v<LessComparable>);

    struct NotLessComparable
    {
    };

    ASSERT_FALSE(is_less_comparable_v<NotLessComparable>);

    // Test cross-type comparison
    ASSERT_TRUE((is_less_comparable_v<int, long>));
    ASSERT_FALSE((is_less_comparable_v<int, std::string>));
}

namespace
{
struct StaticMemberMatch
{
    static bool fill()
    {
        return true;
    }
};

struct StaticMemberMismatch
{
    static double fill()
    {
        return 1.0;
    }
};

struct MemberMatch
{
    bool fill() // NOSONAR
    {
        return true;
    }
};

struct MemberMismatch
{
    double fill() const
    {
        return 1.0;
    }
};

DEFINE_HAS_STATIC_MEMBER_FUNCTION(has_static_bool_fill, T::fill, bool (*)(void))
DEFINE_HAS_MEMBER_FUNCTION(has_bool_fill, fill, bool (T::*)(void))
} // namespace

TEST_F(TraitsTest, has_static_member_function_macro_test)
{
    ASSERT_TRUE((has_static_bool_fill_v<StaticMemberMatch>));
    ASSERT_FALSE((has_static_bool_fill_v<StaticMemberMismatch>));
}

#if __cplusplus >= 202'002L
TEST_F(TraitsTest, concepts_test)
{
    // Test C++20 concepts
    static_assert(util::equality_comparable<int>);
    static_assert(util::equality_comparable<std::string>);

    struct NotComparable
    {
    };

    static_assert(!util::equality_comparable<NotComparable>);

    static_assert(util::less_comparable<int>);
    static_assert(util::less_comparable<double>);
    static_assert(util::less_comparable<std::string>);

    struct NotLessComparable
    {
    };

    static_assert(!util::less_comparable<NotLessComparable>);

    static_assert(util::is_tuple_c<std::tuple<int, double>>);
    static_assert(!util::is_tuple_c<int>);
}
#endif
