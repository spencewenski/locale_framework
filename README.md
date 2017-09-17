Locale Framework
================

Forked from https://github.com/pebble-hacks/locale_framework and setup as a
library for use as a submodule in other pebble projects.

Minimal framework to support locale features in Pebble apps, using
[`i18n_get_system_locale()`](http://developer.getpebble.com/docs/c/group___internationalization.html)
in Pebble Firmware 2.8+ to discover the system locale and select the correct
text to display.

## Set Up Your Project

1. Download the project as a submodule

```bash
git submodule add https://github.com/spencewenski/locale_framework.git src/c/locale_framework
```

2. Add `#include "localize.h"` to any code files that require translation.

3. Call `locale_init()` during app initialization:

```c
int main(void) {
    // Init locale framework
    locale_init();
    // Other app setup code
}
```

4. For all strings that you wish to localize, add `LOCALIZE()` around them.

```c
LOCALIZE("Bacon Pancakes");
```

5. For all locales that you support, add the respective compile flag to your wscipt.
The supported flags directly correspond with the [locales supported by Pebble](https://developer.pebble.com/guides/tools-and-resources/internationalization/#locales-supported-by-pebble):
    - SUPPORTS_EN_US
    - SUPPORTS_FR_FR
    - SUPPORTS_ES_ES
    - SUPPORTS_DE_DE
    - SUPPORTS_IT_IT
    - SUPPORTS_PT_PT
    - SUPPORTS_EN_CN
    - SUPPORTS_EN_TW

For each local that you support, you must have the respective resource ids defined (described below).

Assuming you're starting from the default wscript, it should now look something like this:
```python
# ...
def build(ctx):
    # ...
    for p in ctx.env.TARGET_PLATFORMS:
        ctx.set_env(ctx.all_envs[p])
        ctx.set_group(ctx.env.PLATFORM_NAME)
        # Add compile flags here
        ctx.env.append_value('CFLAGS', ['-DSUPPORTS_EN_US', '-DSUPPORTS_FR_FR, ...])
# ...
```

## Generate Translation Resources

1. Generate locale_en_us.json and locale_en_us.bin from strings wrapped with `LOCALIZE()`:

```bash
src/c/locale_framework/gen_dict.py src/c resources/i18n/locale_en_us.json
```

2. Create a Spanish dictionary from the English dictionary:

```bash
cp resources/i18n/locale_en_us.json resources/i18n/locale_es_es.json
```

3. Translate the Spanish dictionary.

4. Generate the Spanish binary file:

```bash
src/c/locale_framework/dict2bin.py resources/i18n/locale_es_es.json
```

5. Repeat 2-4 for each language you want to support

6. Add the new `.bin` resource files to your project's `package.json` as
[raw resrouces](https://developer.pebble.com/guides/app-resources/raw-data-files/).
The full list of supported resource ids is:
    - LOCALE_EN_US
    - LOCALE_FR_FR
    - LOCALE_ES_ES
    - LOCALE_DE_DE
    - LOCALE_IT_IT
    - LOCALE_PT_PT
    - LOCALE_EN_CN
    - LOCALE_EN_TW

Example locale entries in the `package.json`:
```json
"media": [
    {
        "type": "raw",
        "name": "LOCALE_EN_US",
        "file": "locale_en_us.bin"
    },
    {
        "type": "raw",
        "name": "LOCALE_ES_ES",
        "file": "locale_es_es.bin"
    }
]
```

7. Compile your application and install!

You can easily test your translations by commenting line 20 and uncommenting
line 19 of `localize.c`, replacing "es_ES" with a locale you are translating.

## Add More Languages

If you wish to add more translations in the future, repeat *Generate
Translation Resources* to obtain new translation binary resources. You will also
need to do this in the event that you modify any of your strings.
