<?php

/**
 * @file
 * Admin functionality for the CouchDB Sync module.
 */

/**
 * Form builder: Settings form.
 */
function couchdb_sync_config_form($form, &$form_state) {
  // TODO: Implement an admin UI for choosing which entities to push.
  $form['couchdb_sync_entities'] = array(
    '#type' => 'fieldset',
    '#title' => t('Synced entity types'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Select the entity types which should be synced to Couch DB'),
  );

  $form['couchdb_sync_entities']['couchdb_sync_synced_entities'] = array(
    '#markup' => t('Coming soon'),
  );

  // Load the available processors.
  module_load_include('inc', 'couchdb_sync', 'couchdb_sync.processors');
  $processors = couchdb_sync_get_processor_plugins();

  // Build the options.
  $processor_options = array();
  foreach ($processors as $machine_name => $plugin) {
    $processor_options[$machine_name] = $plugin['name'];
  }

  // Get the current default processor.
  $default_processor = couchdb_sync_get_default_processor_name();

  $form['couchdb_sync_processor'] = array(
    '#type' => 'select',
    '#title' => t('Sync mode'),
    '#description' => t('Select how entities are going to be synced to CouchDB'),
    '#options' => $processor_options,
    '#default_value' => $default_processor,
  );

  $form['couchdb_sync_processor_description'] = array(
    '#markup' => t('The selected sync mode has the following description: %description', array('%description' => $processors[$default_processor]['description'])),
  );

  return system_settings_form($form);
}
