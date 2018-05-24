#include "libc.h"
#include "io.h"
#include "cmos.h"

typedef int(*testfunc) (void);
static unsigned int test_count = 0;
static testfunc tests[100];

int passing_test()
{
    return 0;
}

int test_secs_of_month_jan_2018()
{
    return secs_of_month(1, 18) != 2678400;
}

int test_secs_of_month_feb_2018()
{
    return secs_of_month(2, 18) != 5097600;
}

int test_secs_of_month_mar_2018()
{
    return secs_of_month(3, 18) != (5097600 + 2678400);
}

int test_get_timestamp_from_cmos_reigsters()
{
    uint32_t expected = 1527153647;
    uint32_t actual = get_timestamp_from_cmos_registers(
        47,
        20,
        5,
        24,
        5,
        18
    );
    return (actual - expected) != 0;
}

int test_secs_of_year_2018()
{
    return secs_of_years(17) != 1514764800;
}

int test_vasprintf_with_numbers()
{
    char expected[] = "1527125201 1527125201";
    uint32_t len = strlen(expected);
    char buf[len];
    vasprintf(buf, sizeof(buf)/sizeof(buf[0]), "%d %d", 1527125201, 1527125201);
    return strcmp(buf, expected);
}

int test_vasprintf_escapes_percent_signs()
{
    char expected[] = "%";
    uint32_t len = strlen(expected);
    char buf[len];
    vasprintf(buf, sizeof(buf)/sizeof(buf[0]), "%%");
    print(buf, strlen(buf));
    return strcmp(buf, expected);
}

void test(testfunc test)
{
    tests[test_count++] = test;
}

void run()
{
    print("1..", 3);
    char buf[100];
    vasprintf(buf, sizeof buf / sizeof buf[0], "%d \n", test_count);
    print(buf, strlen(buf));
    for (unsigned int i = 0; i < test_count; i++) {
        testfunc test = tests[i];
        int result = test();
        if (result == 0) {
            char msg[] = "ok";
            print(msg, strlen(msg));
        } else {
            char msg[] = "not ok";
            print(msg, strlen(msg));
        }

        print("\n", 1);
    }
}

extern int testsuite()
{
    test(test_get_timestamp_from_cmos_reigsters);
    test(test_vasprintf_with_numbers);
    test(test_vasprintf_escapes_percent_signs);
    test(passing_test);
    test(test_secs_of_month_jan_2018);
    test(test_secs_of_month_feb_2018);
    test(test_secs_of_month_mar_2018);
    test(test_secs_of_year_2018);

    run();
    return 0;
}

