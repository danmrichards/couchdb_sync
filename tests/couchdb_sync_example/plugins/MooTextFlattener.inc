<?php

/**
 * @file
 * Contains MooTextFlattener.
 */

/**
 * Moo Text Flattener plugin.
 */
final class MooTextFlattener implements CouchDBSyncFlattenerInterface {

  /**
   * {@inheritdoc}
   */
  public function getSupportedFieldType() {
    return 'text';
  }

  /**
   * {@inheritdoc}
   */
  public function flatten(EntityMetadataWrapper $entity_wrapper, $field_name, $multiple = FALSE) {
    // Attempt to get the field value.
    if (isset($entity_wrapper->{$field_name}) && !is_null($entity_wrapper->{$field_name}->value())) {
      // For images strip out some of the core data and append image style URLs.
      $raw_value = $entity_wrapper->{$field_name}->value();

      if ($multiple !== FALSE) {
        return array_map(array($this, 'getMoo'), $raw_value);
      }

      return $this->getMoo($raw_value);
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
  protected function getMoo($value) {
    return 'Moo!';
  }

}
