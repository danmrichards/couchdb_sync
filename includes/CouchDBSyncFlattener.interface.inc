<?php

/**
 * @file
 * Contains CouchDBSyncFlattenerInterface.
 */

/**
 * Interface that all flattener plugins need to implement.
 *
 * Responsible for defining which field type the flatten plugin supports and
 * the heavy lifting of flattening the field value itself.
 */
interface CouchDBSyncFlattenerInterface {

  /**
   * The name of the field type supported by the plugin.
   *
   * @return string
   *   Name of a Drupal field type. Must be a valid field type.
   *
   * @see field_info_field_types
   */
  public function getSupportedFieldType();

  /**
   * Flatten the field value.
   *
   * @param EntityMetadataWrapper $entity_wrapper
   *   A wrapped Drupal entity.
   * @param string $field_name
   *   The name of the field, on the entity, to flatten the value of.
   * @param bool $multiple
   *   Is this a multiple value field?
   *
   * @return mixed
   *   The flattened field value or FALSE if the flatten failed.
   */
  public function flatten(EntityMetadataWrapper $entity_wrapper, $field_name, $multiple = FALSE);

}
