<?php
// $Id: advanced_comment.admin.inc,v 1.1.2.4 2010/05/31 15:10:11 snufkin Exp $

/**
 * @file
 *
 * Adminstrative functions and forms for advanced_comment.
 */

function advanced_comment_admin_form() {
  drupal_add_css(drupal_get_path('module', 'advanced_comment') .'/advanced_comment.css', 'module', 'all', FALSE);
  
  $form = array();
  $form['advanced_comment_core_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default settings for Core'),
    '#description' => t('Use these core comment settings as default when creating a new content type.'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
    '#tree' => TRUE,
  );
  
  // Options provided by core.
  $form['advanced_comment_core_defaults'] = array_merge($form['advanced_comment_core_defaults'], _advanced_comment_core_options());
  
  // Options provided by Advanced comment
  $form['advanced_comment_custom_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default settings for Advanced Comment'),
    '#description' => t('Use these advanced comment settings as the default values.'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
    '#tree' => TRUE,
  );
  $form['advanced_comment_custom_defaults'] = array_merge($form['advanced_comment_custom_defaults'], _advanced_comment_custom_options());

  return system_settings_form($form);
}


/**
 * Create a set of form elements to set core default comment settings.
 *
 * These are form elements from comment_form_alter. Normally these default values
 * are hardcoded in the form (default values in the variable_get). We assign sane
 * defaults here and in a hook_form_alter the original defaults are replaced.
 *
 * On some elements I am using checkbox instead of radio for better UX. Note that this
 * might result in the wrong default value for the radios on the comment form unless
 * a) they have no keys given,
 * b) the second radio value is the enabled version of the checkbox,
 * c) there is a manual "mapping" between the checbkox value and the radio.
 */
function _advanced_comment_core_options() {
  $defaults = variable_get('advanced_comment_core_defaults', advanced_comment_core_defaults());
  $form = array();
  $form['comment'] = array(
    '#title' => t('Commenting'),
    '#type' => 'select',
    '#options' => array(t('Disabled'), t('Read only'), t('Read/Write')),
    '#default_value' => $defaults['comment'],
  );
  $form['comment_default_mode'] = array(
    '#title' => t('Threading'),
    '#type' => 'select',
    '#options' => _comment_get_modes(),
    '#default_value' => $defaults['comment_default_mode'],
  );
  $form['comment_default_order'] = array(
    '#type' => 'select',
    '#title' => t('Ordering'),
    '#options' => _comment_get_orders(),
    '#default_value' => $defaults['comment_default_order'],
  );
  $form['comment_default_per_page'] = array(
    '#title' => t('Number of comments per page'),
    '#type' => 'select',
    '#options' => _comment_per_page(),
    '#default_value' => $defaults['comment_default_per_page'],
  );
  
  $form['comment_controls'] = array(
    '#title' => t('Comment controls'),
    '#type' => 'select',
    '#options' => array(
      t('Display above the comments'),
      t('Display below the comments'),
      t('Display above and below the comments'),
      t('Do not display'),
    ),
    '#default_value' => $defaults['comment_controls'],
  );
  
  $form['comment_anonymous'] = array(
    '#title' => t('Anonymous commenting'),
    '#type' => 'select',
    '#options' => array(
      COMMENT_ANONYMOUS_MAYNOT_CONTACT => t('Anonymous posters may not enter their contact information'),
      COMMENT_ANONYMOUS_MAY_CONTACT => t('Anonymous posters may leave their contact information'),
      COMMENT_ANONYMOUS_MUST_CONTACT => t('Anonymous posters must leave their contact information'),
    ),
    '#default_value' => $defaults['comment_anonymous'],
  );
  // Comment module would disable the anonymous settings form, maybe we should show it and display a notice?
  // Reason: if it changes later this field will not have proper defaults.
  $form['comment_subject_field'] = array(
    '#title' => t('Enable subject field'),
    '#type' => 'checkbox',
    '#default_value' => $defaults['comment_subject_field'],
  );
  $form['comment_preview'] = array(
    '#title' => t('Require comment preview'),
    '#type' => 'checkbox',
    '#default_value' => $defaults['comment_preview'],
  );
  $form['comment_form_location'] = array(
    '#title' => t('Display comment form below posts'),
    '#type' => 'checkbox',
    '#default_value' => $defaults['comment_form_location'],
  );
  return $form;
}

function _advanced_comment_custom_options() {
  $defaults = variable_get('advanced_comment_custom_defaults', advanced_comment_custom_defaults());
  $form = array();
  $form['reply_link'] = array(
    '#title' => t('Hide reply link on flat lists'),
    '#type' => 'checkbox',
    '#default_value' => $defaults['reply_link'],
  );
  $form['edit_link'] = array(
    '#title' => t('Hide edit link on flat lists'),
    '#type' => 'checkbox',
    '#default_value' => $defaults['edit_link'],
  );
/* 
 * In Drupal 6.17 only.
  $form['delete_link'] = array(
    '#title' => t('Show delete link only on the latest comment in flat lists'),
    '#type' => 'checkbox',
    '#default_value' => $defaults['delete_link'],
  );
  */
  return $form;
}
