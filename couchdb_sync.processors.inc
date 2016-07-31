<?php

/**
 * @file
 * Code associated with definition, retrieval and usage of processor plugins.
 */

/**
 * Get all processor plugins.
 *
 * @return array
 *   Array containing information on all available processor plugins.
 */
function couchdb_sync_get_processor_plugins($reset = FALSE) {
  $processors = &drupal_static(__FUNCTION__);

  // If we have no statically cached processors, we need to get them.
  if (NULL === $processors || $reset) {
    ctools_include('plugins');

    // Get the defined plugins.
    $processors = ctools_get_plugins('couchdb_sync', 'processors');

    // Check the parser plugins extend the correct base class.
    $processors = array_filter($processors, '_couchdb_sync_validate_processor_plugin', ARRAY_FILTER_USE_KEY);
  }

  return $processors;
}

/**
 * Get one processor plugin.
 *
 * @param string $name
 *   Name of the processor plugin to get.
 *
 * @return mixed
 *   Array containing information on the specified processor plugins or FALSE if
 *   the plugin does not extend the correct class.
 */
function couchdb_sync_get_processor_plugin_by_name($name) {
  ctools_include('plugins');

  // Get the plugin.
  $parser = ctools_get_plugins('couchdb_sync', 'processors', $name);

  return _couchdb_sync_validate_processor_plugin($name) ? $parser : FALSE;
}

/**
 * Gets the name of the default processor.
 *
 * @return string
 *   Name of the processor.
 */
function couchdb_sync_get_default_processor_name() {
  $processor = variable_get('couchdb_sync_processor', NULL);

  // If we don't have a default set, just use the first available plugin.
  if (is_null($processor)) {
    module_load_include('inc', 'couchdb_sync', 'couchdb_sync.processors');
    $processor_names = array_keys(couchdb_sync_get_processor_plugins());
    $processor = reset($processor_names);
  }

  return $processor;
}

/**
 * Gets the default processor plugin.
 *
 * @param bool $reset
 *   Force a reset of the static processor cache.
 *
 * @return CouchDBSyncProcessorInterface
 *   Instantiated processor object.
 */
function couchdb_sync_get_processor_plugin($reset = FALSE) {
  $processor = &drupal_static(__FUNCTION__);

  // Return the statically cached processor if present.
  if (isset($processor) && !$reset) {
    return $processor;
  }

  // Load the plugin object.
  $processor = _couchdb_sync_load_plugin_object('processors', couchdb_sync_get_default_processor_name());

  return $processor;
}

/**
 * Validate that a processor plugin extends the correct base class.
 *
 * @param string $id
 *   CTools ID of the processor plugin.
 *
 * @return bool
 *   Does the plugin extend the correct base class?
 */
function _couchdb_sync_validate_processor_plugin($id) {
  $class_name = ctools_plugin_load_class('couchdb_sync', 'processors', $id, 'handler');
  return !is_null($class_name) && class_implements($class_name, CouchDBSyncProcessorInterface::class);
}
