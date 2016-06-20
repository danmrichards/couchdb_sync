<?php

/**
 * @file
 * Contains ListTextFlattener.
 */

/**
 * CouchDB Sync Flattener plugin for 'list_text' fields.
 */
final class ListTextFlattener implements CouchDBSyncFlattenerInterface {

  /**
   * {@inheritdoc}
   */
  public function getSupportedFieldType() {
    return 'list_text';
  }

  /**
   * {@inheritdoc}
   */
  public function flatten(EntityMetadataWrapper $entity_wrapper, $field_name) {
    // Attempt to get the field value.
    if (isset($entity_wrapper->{$field_name}) && !is_null($entity_wrapper->{$field_name}->value())) {
      // Get the list value.
      $value = $entity_wrapper->{$field_name}->value();

      // Loop through each field value and substitue the raw value for the human
      // readable version.
      foreach ($value as $delta => $list_value) {
        $value[$delta] = $field_info['settings']['allowed_values'][$list_value];
      }

      return $value;
    }
    else {
      return FALSE;
    }
  }

}
