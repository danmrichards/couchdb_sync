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
    '#ajax' => array(
      'callback' => 'couchdb_sync_processor_callback',
      'wrapper' => 'couchdb-sync-processor-description',
    ),
  );

  // Determine the processor description.
  if (isset($form_state['values']['couchdb_sync_processor']) && !empty($processors[$form_state['values']['couchdb_sync_processor']]['description'])) {
    $description = $processors[$form_state['values']['couchdb_sync_processor']]['description'];
  }
  else {
    $description = $processors[$default_processor]['description'];
  }

  $form['couchdb_sync_processor_description'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="couchdb-sync-processor-description">',
    '#suffix' => '</div>',
    '#markup' => t('The selected sync mode has the following description: %description', array('%description' => $description)),
  );

  return system_settings_form($form);
}

/**
 * Form AJAX callback: Update the selected processor description.
 */
function couchdb_sync_processor_callback($form, $form_state) {
  return $form['couchdb_sync_processor_description'];
}
