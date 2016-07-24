<?php

/**
 * @file
 * Contains TextWithSummaryFlattener.
 */

/**
 * CouchDB Sync Flattener plugin for 'text_with_summary' fields.
 */
final class TextWithSummaryFlattener implements CouchDBSyncFlattenerInterface {

  /**
   * {@inheritdoc}
   */
  public function getSupportedFieldType() {
    return 'text_with_summary';
  }

  /**
   * {@inheritdoc}
   */
  public function flatten(EntityMetadataWrapper $entity_wrapper, $field_name, $multiple = FALSE) {
    // Attempt to get the field value.
    if (isset($entity_wrapper->{$field_name}) && !is_null($entity_wrapper->{$field_name}->value())) {
      $raw_value = $entity_wrapper->{$field_name}->value();

      // TODO: Implement multiple value handling.

      // Just return the safe values.
      return array(
        'summary' => $raw_value['safe_summary'],
        'value' => $raw_value['safe_value'],
      );
    }
    else {
      return FALSE;
    }
  }

}
