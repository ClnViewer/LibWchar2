
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_iswpunct)
{
    ck_assert_msg((&iswpunct == &_iswpunct), 0, "iswpunct NO equals! libc used!");
}
END_TEST
