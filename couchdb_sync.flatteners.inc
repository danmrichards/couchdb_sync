<?php

/**
 * @file
 * Code associated with definition, retrieval and usage of flattener plugins.
 */

/**
 * Get all flattener plugins.
 *
 * @return array
 *   Array containing information on all available flattener plugins.
 */
function couchdb_sync_get_flattener_plugins($reset = FALSE) {
  $flatteners = &drupal_static(__FUNCTION__);

  // If we have no statically cached flatteners, we need to get them.
  if (NULL === $flatteners || $reset) {
    ctools_include('plugins');

    // Get the defined plugins.
    $flatteners = ctools_get_plugins('couchdb_sync', 'flatteners');

    // Check the parser plugins extend the correct base class.
    $flatteners = array_filter($flatteners, '_couchdb_sync_validate_flattener_plugin', ARRAY_FILTER_USE_KEY);
  }

  return $flatteners;
}

/**
 * Get one flattener plugin.
 *
 * @param string $name
 *   Name of the flattener plugin to get.
 *
 * @return mixed
 *   Array containing information on the specified flattener plugins or FALSE if
 *   the plugin does not extend the correct class.
 */
function couchdb_sync_get_flattener_plugin($name) {
  ctools_include('plugins');

  // Get the plugin.
  $parser = ctools_get_plugins('couchdb_sync', 'flatteners', $name);

  return _couchdb_sync_validate_flattener_plugin($name) ? $parser : FALSE;
}

/**
 * Get a list of flatteners with their allocated field type.
 *
 * @param bool $reset
 *   Reset the flattener plugins static cache.
 *
 * @return array
 *   Array of flattener plugins keyed by their allocated field type.
 */
function couchdb_sync_get_flatteners_by_type($reset = FALSE) {
  $flatteners = &drupal_static(__FUNCTION__);

  // Check if we have statically cached flatteners and no reset flag was passed.
  if (isset($flatteners) && !$reset) {
    return $flatteners;
  }

  $flatteners = array();

  // Loop through available flatteners.
  foreach (couchdb_sync_get_flattener_plugins() as $name => $plugin) {
    // Get the plugin object.
    $plugin_object = _couchdb_sync_load_flattener_object('flatteners', $name);

    // Get the field type the plugin supports.
    $plugin_field_type = $plugin_object->getSupportedFieldType();

    // Allocate the field type to this plugin, or throw an error if it has been
    // allocated to another plugin already.
    if (!isset($flatteners[$plugin_field_type])) {
      $flatteners[$plugin_field_type] = $name;
    }
    else {
      throw new CouchDBSyncException(t('Flattener plugin (@name) attempted to use field type already allocated.', array('@name' => $name)));
    }
  }

  return $flatteners;
}

/**
 * Get an flattener plugin object for the requested field type.
 *
 * @param string $field_type
 *   Type of field being flattened. Must be a valid field type.
 * @param bool $reset
 *   Force a reset of the static flattener cache.
 *
 * @return CouchDBSyncFlattenerInterface
 *   Instantiated flattener object.
 *
 * @see field_info_field_types
 */
function couchdb_sync_get_field_type_flattener($field_type, $reset = FALSE) {
  $flattener = &drupal_static(__FUNCTION__);

  // Return the statically cached flattener if present.
  if (isset($flattener[$field_type]) && !$reset) {
    return $flattener[$field_type];
  }

  // Get the list of valid field types.
  $field_types = array_keys(field_info_field_types());

  // Ensure we have a valid field type.
  if (!in_array($field_type, $field_types)) {
    throw new CouchDBSyncException(t('Could not get flattener: Invalid field type specified'));
  }

  // Get the list of flatteners.
  $flatteners_by_type = couchdb_sync_get_flatteners_by_type();

  // Get the correct plugin for this field type, or use the generic fallback.
  $flattener_plugin_name = !empty($flatteners_by_type[$field_type]) ? $flatteners_by_type[$field_type] : $flatteners_by_type[COUCHDB_SYNC_GENERIC_FIELD_INDICATOR];

  // Load the plugin object.
  $flattener[$field_type] = _couchdb_sync_load_flattener_object('flatteners', $flattener_plugin_name);

  return $flattener[$field_type];
}

/**
 * Validate that a flattener plugin extends the correct base class.
 *
 * @param string $id
 *   CTools ID of the flattener plugin.
 *
 * @return bool
 *   Does the plugin extend the correct base class?
 */
function _couchdb_sync_validate_flattener_plugin($id) {
  $class_name = ctools_plugin_load_class('couchdb_sync', 'flatteners', $id, 'handler');
  return !is_null($class_name) && class_implements($class_name, CouchDBSyncFlattenerInterface::class);
}

/**
 * Load the class for a given plugin.
 *
 * @param string $type
 *   Type of plugin we're loading.
 * @param string $name
 *   Name of the CTools plugin to load.
 *
 * @return mixed
 *   An instantiated plugin object or FALSE if it could not be instantiated.
 */
function _couchdb_sync_load_flattener_object($type, $name) {
  ctools_include('plugins');
  $class_name = ctools_plugin_load_class('couchdb_sync', $type, $name, 'handler');

  return (!is_null($class_name) && class_exists($class_name)) ? new $class_name() : FALSE;
}
