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

      if ($multiple !== FALSE) {
        return array_map(array($this, 'parseValue'), $raw_value);
      }

      return $this->parseValue($raw_value);
    }
    else {
      return FALSE;
    }
  }


  /**
   * Parse a single field value into the desired format.
   *
   * @param array $value
   *   The raw value of the field.
   *
   * @return array
   *   Parsed field value array.
   */
  protected function parseValue($value) {
    return array(
      'summary' => $value['safe_summary'],
      'value' => $value['safe_value'],
    );
  }

}
