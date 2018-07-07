
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_iswgraph)
{
    ck_assert_msg((&iswgraph == &_iswgraph), 0, "iswgraph NO equals! libc used!");
}
END_TEST
