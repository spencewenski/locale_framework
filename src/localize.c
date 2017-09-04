#include <pebble.h>

DictionaryIterator s_locale_dict;

/**
 * Get the resource id for the file that contains the translated strings for
 * the given locale.
 *
 * @param  locale_str String that contains the current locale.
 * @return            The resource id for the file that contains the translated
 *                    strings for the given locale.
 */
static uint32_t get_locale_resource_id(const char* locale_str);

void locale_init(void) {

  // Detect system locale
  //hard-coded for testing
  // const char* locale_str = "es_ES";
  const char* locale_str = i18n_get_system_locale();
  ResHandle locale_handle = resource_get_handle(get_locale_resource_id(locale_str));
  int locale_size = resource_size(locale_handle);

  int resource_offset = 0;
  int locale_entries = 0;
  resource_offset += resource_load_byte_range(locale_handle, resource_offset,
      (uint8_t*)&locale_entries, sizeof(locale_entries));

  struct locale {
    int32_t hashval;
    int32_t strlen;
  } locale_info;

  int dict_buffer_size = locale_size + 7 * locale_entries; //7 byte header per item
  char *dict_buffer = malloc(dict_buffer_size);
  dict_write_begin(&s_locale_dict, (uint8_t*)dict_buffer, dict_buffer_size);

  for (int i = 0; i < locale_entries; i++) {
    resource_offset += resource_load_byte_range(locale_handle,
                                                resource_offset,
                                                (uint8_t*)&locale_info,
                                                sizeof(struct locale));
    char *buffer = malloc(locale_info.strlen);
    resource_offset += resource_load_byte_range(locale_handle,
                                                resource_offset,
                                                (uint8_t*)buffer,
                                                locale_info.strlen);
    dict_write_cstring(&s_locale_dict, locale_info.hashval, buffer);
    free(buffer);
  }

  dict_write_end(&s_locale_dict);
}

char *locale_str(int hashval) {
  Tuple *tupl = dict_find(&s_locale_dict, hashval);

  if (tupl && tupl->value->cstring) {
    return tupl->value->cstring;
  }
  return "\7"; //return blank character
}

static uint32_t get_locale_resource_id(const char* locale_str) {
#ifdef SUPPORTS_FR_FR
  if (strcmp(locale_str, "fr_FR") == 0) {
    return RESOURCE_ID_LOCALE_FR_FR;
  }
#endif
#ifdef SUPPORTS_ES_ES
  if (strcmp(locale_str, "es_ES") == 0) {
    return RESOURCE_ID_LOCALE_ES_ES;
  }
#endif
#ifdef SUPPORTS_DE_DE
  if (strcmp(locale_str, "de_DE") == 0) {
    return RESOURCE_ID_LOCALE_DE_DE;
  }
#endif
#ifdef SUPPORTS_IT_IT
  if (strcmp(locale_str, "it_IT") == 0) {
    return RESOURCE_ID_LOCALE_IT_IT;
  }
#endif
#ifdef SUPPORTS_PT_PT
  if (strcmp(locale_str, "pt_PT") == 0) {
    return RESOURCE_ID_LOCALE_PT_PT;
  }
#endif
#ifdef SUPPORTS_EN_CN
  if (strcmp(locale_str, "en_CN") == 0) {
    return RESOURCE_ID_LOCALE_EN_CN;
  }
#endif
#ifdef SUPPORTS_EN_TW
  if (strcmp(locale_str, "en_TW") == 0) {
    return RESOURCE_ID_LOCALE_EN_TW;
  }
#endif
  // Fall back to English
  return RESOURCE_ID_LOCALE_EN_US;
}
