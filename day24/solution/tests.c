#define _POSIX_C_SOURCE 200809L

#include "scanner.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int g_assertions = 0;
static int g_failures = 0;

static void assert_true(bool cond, const char* test_name, const char* detail) {
    ++g_assertions;
    if (!cond) {
        ++g_failures;
        fprintf(stderr, "[FAIL] %s: %s\n", test_name, detail);
    }
}

static FILE* tmpfile_from_text(const char* text) {
    FILE* fp = tmpfile();
    if (fp == NULL) {
        return NULL;
    }
    if (text != NULL && fputs(text, fp) == EOF) {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    return fp;
}

static char* read_file_to_string(FILE* fp) {
    long sz = 0;
    char* out = NULL;

    if (fp == NULL) {
        return NULL;
    }
    if (fseek(fp, 0, SEEK_END) != 0) {
        return NULL;
    }
    sz = ftell(fp);
    if (sz < 0) {
        return NULL;
    }
    if (fseek(fp, 0, SEEK_SET) != 0) {
        return NULL;
    }

    out = (char*)malloc((size_t)sz + 1u);
    if (out == NULL) {
        return NULL;
    }
    if (sz > 0) {
        size_t nread = fread(out, 1u, (size_t)sz, fp);
        if (nread != (size_t)sz) {
            free(out);
            return NULL;
        }
    }
    out[sz] = '\0';
    return out;
}

static int run_scanner_capture(FILE* input_fp,
                               const matcher_t* m,
                               const scan_opts_t* opts,
                               char** captured_out) {
    int saved_stdout_fd = -1;
    int out_fd = -1;
    FILE* capture = tmpfile();
    int rc = -1;

    *captured_out = NULL;
    if (capture == NULL) {
        return -1;
    }

    fflush(stdout);
    saved_stdout_fd = dup(fileno(stdout));
    out_fd = fileno(capture);
    if (saved_stdout_fd < 0 || out_fd < 0) {
        fclose(capture);
        if (saved_stdout_fd >= 0) {
            close(saved_stdout_fd);
        }
        return -1;
    }

    if (dup2(out_fd, fileno(stdout)) < 0) {
        close(saved_stdout_fd);
        fclose(capture);
        return -1;
    }

    rc = scanner_run(input_fp, m, opts);

    fflush(stdout);
    (void)dup2(saved_stdout_fd, fileno(stdout));
    close(saved_stdout_fd);

    rewind(capture);
    *captured_out = read_file_to_string(capture);
    fclose(capture);
    return rc;
}

static void test_single_match(void) {
    matcher_t m;
    scan_opts_t opts = {false, false, NULL};
    FILE* in = NULL;
    char* out = NULL;
    int rc = 0;

    assert_true(matcher_init(&m, "apple", false), "test_single_match", "matcher init");
    in = tmpfile_from_text("apple\nbanana\n");
    assert_true(in != NULL, "test_single_match", "tmpfile input");
    if (in == NULL) {
        matcher_destroy(&m);
        return;
    }

    rc = run_scanner_capture(in, &m, &opts, &out);
    assert_true(rc == 1, "test_single_match", "one match expected");
    assert_true(out != NULL, "test_single_match", "captured output present");
    if (out != NULL) {
        assert_true(strcmp(out, "apple\n") == 0, "test_single_match", "single line output");
    }

    free(out);
    fclose(in);
    matcher_destroy(&m);
}

static void test_multiple_matches_and_count(void) {
    matcher_t m;
    scan_opts_t opts = {false, false, NULL};
    FILE* in = NULL;
    char* out = NULL;
    int rc = 0;

    assert_true(matcher_init(&m, "ban", true), "test_multiple_matches_and_count", "matcher init");
    in = tmpfile_from_text("apple\nBanana\nbanana split\npear\n");
    assert_true(in != NULL, "test_multiple_matches_and_count", "tmpfile input");
    if (in == NULL) {
        matcher_destroy(&m);
        return;
    }

    rc = run_scanner_capture(in, &m, &opts, &out);
    assert_true(rc == 2, "test_multiple_matches_and_count", "two matches expected");
    assert_true(out != NULL, "test_multiple_matches_and_count", "captured output");

    free(out);
    fclose(in);
    matcher_destroy(&m);
}

static void test_no_matches(void) {
    matcher_t m;
    scan_opts_t opts = {false, false, NULL};
    FILE* in = NULL;
    char* out = NULL;
    int rc = 0;

    assert_true(matcher_init(&m, "zzz", false), "test_no_matches", "matcher init");
    in = tmpfile_from_text("alpha\nbeta\n");
    assert_true(in != NULL, "test_no_matches", "tmpfile input");
    if (in == NULL) {
        matcher_destroy(&m);
        return;
    }

    rc = run_scanner_capture(in, &m, &opts, &out);
    assert_true(rc == 0, "test_no_matches", "zero matches expected");
    assert_true(out != NULL, "test_no_matches", "captured output present");
    if (out != NULL) {
        assert_true(strcmp(out, "") == 0, "test_no_matches", "no output for no matches");
    }

    free(out);
    fclose(in);
    matcher_destroy(&m);
}

static void test_filename_prefix_and_lineno_prefix(void) {
    matcher_t m;
    scan_opts_t opts = {true, true, "f.txt"};
    FILE* in = NULL;
    char* out = NULL;
    int rc = 0;

    assert_true(matcher_init(&m, "a", false), "test_filename_prefix_and_lineno_prefix", "matcher init");
    in = tmpfile_from_text("a\nb\na\n");
    assert_true(in != NULL, "test_filename_prefix_and_lineno_prefix", "tmpfile input");
    if (in == NULL) {
        matcher_destroy(&m);
        return;
    }

    rc = run_scanner_capture(in, &m, &opts, &out);
    assert_true(rc == 2, "test_filename_prefix_and_lineno_prefix", "two matches expected");
    assert_true(out != NULL, "test_filename_prefix_and_lineno_prefix", "captured output present");
    if (out != NULL) {
        assert_true(strstr(out, "f.txt:1:a") != NULL,
                    "test_filename_prefix_and_lineno_prefix",
                    "filename+lineno prefix for first match");
    }

    free(out);
    fclose(in);
    matcher_destroy(&m);
}

static void test_empty_input_file(void) {
    matcher_t m;
    scan_opts_t opts = {false, false, NULL};
    FILE* in = tmpfile_from_text("");
    char* out = NULL;
    int rc = 0;

    assert_true(matcher_init(&m, "x", false), "test_empty_input_file", "matcher init");
    assert_true(in != NULL, "test_empty_input_file", "tmpfile input");
    if (in == NULL) {
        matcher_destroy(&m);
        return;
    }

    rc = run_scanner_capture(in, &m, &opts, &out);
    assert_true(rc == 0, "test_empty_input_file", "empty input should produce 0 matches");
    assert_true(out != NULL, "test_empty_input_file", "captured output present");

    free(out);
    fclose(in);
    matcher_destroy(&m);
}

int main(void) {
    test_single_match();
    test_multiple_matches_and_count();
    test_no_matches();
    test_filename_prefix_and_lineno_prefix();
    test_empty_input_file();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
