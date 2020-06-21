#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/utsname.h>
#include <sys/system_properties.h>

struct prop {
    char *key_name;
    char *prop_name;
};

static void system_kernel(void)
{
    struct utsname uts;
    char build_host[512];
    char build_user[512];

    __system_property_get("ro.build.host", build_host);
    __system_property_get("ro.build.user", build_user);

    if (uname(&uts) != -1) {
        printf("%-25s: %s %s %s@%s %s %s\n", "Kernel version", uts.sysname,
                uts.release, build_user, build_host, uts.version, uts.machine);
    }
}

static void system_cpu(void)
{
    int i, fd, bytes;
    char *p;
    char buffer[1024];
    const char *needle = "Processor    :";

    fd = open("/proc/cpuinfo", O_RDONLY);
    if (fd == -1) {
        return;
    }

    bytes = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes == -1) {
        return;
    }

    buffer[bytes] = '\0';
    p = buffer;

    p = strstr(p, "Processor	:");
    p += strlen(needle) - 1;

    printf("%-25s: ", "CPU");
    while ( *p != '\n') {
        printf("%c", *p++);
    }

    printf("\n");

    close(fd);
}

static void system_properties(struct prop *array, int size)
{
    int i, len;
    char value[1024] = {0};

    for (i=0; i < size; i++) {
        if (i == 4)
            system_kernel();

        len = __system_property_get(array[i].prop_name, value);
        value[len] = '\0';
        printf("%-25s: %s\n", array[i].key_name, value);
    }

    system_cpu();
}

int
main(void)
{
    struct prop props[] = {
        {.key_name = "Model number", .prop_name = "ro.product.model"},
        {.key_name = "Android codename", .prop_name = "ro.build.product"},
        {.key_name = "Android version", .prop_name = "ro.build.version.release"},
        {.key_name = "Android SDK version", .prop_name = "ro.build.version.sdk"},
        {.key_name = "Baseband version", .prop_name = "gsm.version.baseband"},
        {.key_name = "Build number", .prop_name = "ro.build.display.id"},
    };

    system_properties(props, sizeof(props) / sizeof(props[0]));

    return (0);
}
