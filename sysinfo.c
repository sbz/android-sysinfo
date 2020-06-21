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

struct android_version {
    char *number;
    char *name;
};

char *
android_to_name(const char *version)
{
    int i;
    char *name = NULL;

    /* https://en.wikipedia.org/wiki/Android_version_history#Overview */
    struct android_version versions[] = {
        {"9.0",     "Pie"},
        {"8.0",     "Oreo"},
        {"7.0",     "Nougat"},
        {"6.0",     "Marshmallow"},
        {"5.0",     "Lollipop"},
        {"4.4",     "KitKat"},
        {"4.1",     "Jelly Bean"},
        {"4.0",     "Ice Cream Sandwich"},
        {"3.0",     "Honeycomb"},
        {"2.3",     "Gingerbread"},
        {"2.2",     "Froyo"},
        {"2.0",     "Eclair"},
        {"1.6",     "Donut"},
        {"1.5",     "Cupcake"},
    };


    for (i = 0; i < (sizeof(versions) / sizeof(versions[0])); i++ ) {
        if (!strncmp(version, versions[i].number, 3)) {
            name = versions[i].name;
            break;
        }
    }

    if (name == NULL) {
        for (i = 0; i < (sizeof(versions) / sizeof(versions[0])); i++ ) {
            if (!strncmp(version, versions[i].number, 1)) {
                name = versions[i].name;
                break;
            }
        }
    }

    if (name == NULL)
        name = "Unknow";

    return (name);
}

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
        if (i == 2) {
            printf("%-25s: %s", array[i].key_name, value);
            printf(" (%s)\n", android_to_name(value));
        } else {
            printf("%-25s: %s\n", array[i].key_name, value);
        }
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
