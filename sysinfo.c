#include <stdio.h>

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
