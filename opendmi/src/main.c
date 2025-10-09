#include <stdlib.h>
#include <stdio.h>

#include <opendmi/context.h>

int main(int argc, char *argv[])
{
    // Open DMI context
    dmi_context_t *dmi = dmi_open();
    if (dmi == nullptr) {
        printf("Unable to open DMI context: %s\n", dmi_error_message(dmi_get_error(nullptr)));
        return EXIT_FAILURE;
    }

    // Close DMI context
    dmi_close(dmi);

    return EXIT_SUCCESS;
}
