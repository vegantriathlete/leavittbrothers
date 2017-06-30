<?php

/**
 * @file
 * Rules integration for Leavitt Brothers Subscription functionality
 */

/**
 * Implements hook_rules_event_info().
 */
function lb_subscription_rules_event_info() {
  $items = array(
    'lb_subscription_purchase' => array(
      'label' => t('After purchasing a subscription'),
      'group' => t('LB Subscription'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User purchasing the subscription'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundle' => 'subscription',
          'label' => t('Subscription purchased'),
        ),
        'payment_type' => array(
          'type' => 'text',
          'label' => t('The payment type'),
        ),
        'billing_period' => array(
          'type' => 'text',
          'label' => t('The billing period of the subscription'),
        ),
        'renewal_date' => array(
          'type' => 'text',
          'label' => t('The renewal date of the subscription'),
        ),
        'renewal_date_formatted' => array(
          'type' => 'text',
          'label' => t('The formatted renewal date of the subscription'),
        ),
      ),
    ),
    'lb_subscription_cancel' => array(
      'label' => t('After canceling a subscription'),
      'group' => t('LB Subscription'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User canceling the subscription'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundle' => 'subscription',
          'label' => t('Subscription cancel'),
        ),
      ),
    ),
    'lb_subscription_renewal_success' => array(
      'label' => t('After a successful subscription automatic renewal'),
      'group' => t('LB Subscription'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User whose subscription was renewed'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundle' => 'subscription',
          'label' => t('Subscription renewed'),
        ),
        'billing_period' => array(
          'type' => 'text',
          'label' => t('The billing period of the subscription'),
        ),
        'renewal_date' => array(
          'type' => 'text',
          'label' => t('The renewal date of the subscription'),
        ),
        'renewal_date_formatted' => array(
          'type' => 'text',
          'label' => t('The formatted renewal date of the subscription'),
        ),
      ),
    ),
    'lb_subscription_renewal_failure' => array(
      'label' => t('After an unsuccessful subscription automatic renewal'),
      'group' => t('LB Subscription'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User whose subscription was not renewed'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundle' => 'subscription',
          'label' => t('Subscription not renewed'),
        ),
        'amount' => array(
          'type' => 'text',
          'label' => t('$ Amount being processed'),
        ),
        'error' => array(
          'type' => 'text',
          'label' => t('Error message from the PayPal server'),
        ),
      ),
    ),
    'lb_subscription_refresh_failure' => array(
      'label' => t('After an unsuccessful token refresh'),
      'group' => t('LB Subscription'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User whose subscription was not renewed'),
        ),
      ),
    ),
    'lb_subscription_missing_renewal_information' => array(
      'label' => t('When missing information to finish processing a renewal'),
      'group' => t('LB Subscription'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User whose subscription is supposed to be renewed'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundle' => 'subscription',
          'label' => t('Subscription that is supposed to be renewed'),
        ),
        'amount' => array(
          'type' => 'text',
          'label' => t('The amount charged for the subscription'),
        ),
        'billing_period' => array(
          'type' => 'text',
          'label' => t('The billing period of the subscription'),
        ),
        'renewal_date' => array(
          'type' => 'text',
          'label' => t('The renewal date of the subscription'),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implements hook_rules_action_info().
 */
function lb_subscription_rules_action_info() {
  $items = array(
    'lb_subscription_grant_role' => array(
      'label' => t('Grant a role for a subscription purchase'),
      'group' => t('LB Subscription'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User who purchased subscription'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundles' => array('subscription'),
          'label' => t('Subscription that was purchased'),
        ),
      ),
    ),
    'lb_subscription_set_subscription' => array(
      'label' => t('Set subscription after a subscription purchase'),
      'group' => t('LB Subscription'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User who purchased subscription'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundles' => array('subscription'),
          'label' => t('Subscription that was purchased'),
        ),
      ),
    ),
    'lb_subscription_set_payment_type' => array(
      'label' => t('Set payment type after a subscription purchase'),
      'group' => t('LB Subscription'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User who purchased subscription'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundles' => array('subscription'),
          'label' => t('Subscription that was purchased'),
        ),
        'payment_type' => array(
          'type' => 'text',
          'label' => t('Payment type that was used'),
        ),
      ),
    ),
    'lb_subscription_set_billing_period' => array(
      'label' => t('Set the billing period after a subscription purchase'),
      'group' => t('LB Subscription'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User who purchased subscription'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundles' => array('subscription'),
          'label' => t('Subscription that was purchased'),
        ),
        'billing_period' => array(
          'type' => 'text',
          'label' => t('The billing period paid for'),
        ),
      ),
    ),
    'lb_subscription_set_renewal_date' => array(
      'label' => t('Set the renewal date after a subscription purchase'),
      'group' => t('LB Subscription'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User who purchased subscription'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundles' => array('subscription'),
          'label' => t('Subscription that was purchased'),
        ),
        'renewal_date' => array(
          'type' => 'text',
          'label' => t('The renewal date of the subscription'),
        ),
      ),
    ),
    'lb_subscription_set_renewal_flag' => array(
      'label' => t('Set renewal flag after a subscription purchase'),
      'group' => t('LB Subscription'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User who purchased subscription'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundles' => array('subscription'),
          'label' => t('Subscription that was purchased'),
        ),
        'payment_type' => array(
          'type' => 'text',
          'label' => t('Payment type that was used'),
        ),
      ),
    ),
    'lb_subscription_revoke_role' => array(
      'label' => t('Revoke a role when a subscription expires'),
      'group' => t('LB Subscription'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User whose subscription expired'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundles' => array('subscription'),
          'label' => t('Subscription that expired'),
        ),
      ),
    ),
    'lb_subscription_remove_subscription' => array(
      'label' => t('Remove a subscription when it expires'),
      'group' => t('LB Subscription'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User whose subscription expired'),
        ),
        'subscription' => array(
          'type' => 'node',
          'bundles' => array('subscription'),
          'label' => t('Subscription that expired'),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Grant a role when a subscription is purchased
 *
 * @param object $account
 *   The user account to be granted the role
 * @param object $subscription
 *   The fully loaded node object of the subscription that was purchased
 */
function lb_subscription_grant_role($account, $subscription) {
  user_multiple_role_edit(array($account->uid), 'add_role', $subscription->field_assign_role[LANGUAGE_NONE][0]['rid']);
}

/**
 * Set the subscription when a subscription is purchased
 *
 * @param object $account
 *   The user account to be granted the role
 * @param object $subscription
 *   The fully loaded node object of the subscription that was purchased
 */
function lb_subscription_set_subscription($account, $subscription) {
  // The $account that rules passes contains the original information, which may have
  // changed as a result of an action that has run.
  $entity = entity_load_single('user', $account->uid);
  $account_subscription_data = lb_subscription_retrieve_account_subscription_data($entity, $subscription);
  if ($account_subscription_data['delta'] === NULL) {
    $entity = entity_load_single('user', $account->uid);
    if ($account_subscription_data['subscriptions']) {
      $index = count($entity->field_subscription[LANGUAGE_NONE]);
    }
    else {
      $index = 0;
    }
    $entity->field_subscription[LANGUAGE_NONE][$index] = array(
      'field_subscription_reference' => array(
        LANGUAGE_NONE => array(
          0 => array(
            'target_id' => $subscription->nid,
          ),
        ),
      ),
    );
    entity_save('user', $entity);
  }
}

/**
 * Set the payment type when a subscription is purchased
 *
 * @param object $account
 *   The user account to be granted the role
 * @param object $subscription
 *   The fully loaded node object of the subscription that was purchased
 * @param string $payment_type
 *   The payment type used to make the purchase
 */
function lb_subscription_set_payment_type($account, $subscription, $payment_type) {
  // The $account that rules passes contains the original information, which may have
  // changed as a result of an action that has run.
  $entity = entity_load_single('user', $account->uid);
  $account_subscription_data = lb_subscription_retrieve_account_subscription_data($entity, $subscription);
  if ($account_subscription_data['delta'] === NULL) {
    lb_subscription_set_subscription($entity, $subscription);
    $entity = entity_load_single('user', $account->uid);
    $account_subscription_data = lb_subscription_retrieve_account_subscription_data($entity, $subscription);
  }
  if ($account_subscription_data['delta'] !== NULL) {
    if ($account_subscription_data['payment_type'] != $payment_type) {
      $entity->field_subscription[LANGUAGE_NONE][$account_subscription_data['delta']]['field_payment_type'] = array(
        LANGUAGE_NONE => array(
          0 => array(
            'value' => $payment_type,
          ),
        ),
      );
      entity_save('user', $entity);
    }
  }
}

/**
 * Set the billing period when a subscription is purchased
 *
 * @param object $account
 *   The user account to be granted the role
 * @param object $subscription
 *   The fully loaded node object of the subscription that was purchased
 * @param string $billing_period
 *   The billing period for the subscription monthly/annual
 */
function lb_subscription_set_billing_period($account, $subscription, $billing_period) {
  // The $account that rules passes contains the original information, which may have
  // changed as a result of an action that has run.
  $entity = entity_load_single('user', $account->uid);
  $account_subscription_data = lb_subscription_retrieve_account_subscription_data($entity, $subscription);
  if ($account_subscription_data['delta'] === NULL) {
    lb_subscription_set_subscription($entity, $subscription);
    $entity = entity_load_single('user', $account->uid);
    $account_subscription_data = lb_subscription_retrieve_account_subscription_data($entity, $subscription);
  }
  if ($account_subscription_data['delta'] !== NULL) {
    if ($account_subscription_data['billing_period'] != $billing_period) {
      $entity->field_subscription[LANGUAGE_NONE][$account_subscription_data['delta']]['field_billing_period'] = array(
        LANGUAGE_NONE => array(
          0 => array(
            'value' => $billing_period,
          ),
        ),
      );
      entity_save('user', $entity);
    }
  }
}

/**
 * Set the renewal date when a subscription is purchased
 *
 * @param object $account
 *   The user account to be granted the role
 * @param object $subscription
 *   The fully loaded node object of the subscription that was purchased
 * @param string $renewal_date
 *   The YYYYMMDD renewal date for the subscription
 */
function lb_subscription_set_renewal_date($account, $subscription, $renewal_date) {
  // The $account that rules passes contains the original information, which may have
  // changed as a result of an action that has run.
  $entity = entity_load_single('user', $account->uid);
  $account_subscription_data = lb_subscription_retrieve_account_subscription_data($entity, $subscription);
  if ($account_subscription_data['delta'] === NULL) {
    lb_subscription_set_subscription($account, $subscription);
    $entity = entity_load_single('user', $account->uid);
    $account_subscription_data = lb_subscription_retrieve_account_subscription_data($entity, $subscription);
  }
  if ($account_subscription_data['delta'] !== NULL) {
    $entity->field_subscription[LANGUAGE_NONE][$account_subscription_data['delta']]['field_renewal_date'] = array(
      LANGUAGE_NONE => array(
        0 => array(
          'value' => $renewal_date,
          'format' => NULL,
          'safe_value' => $renewal_date,
        ),
      ),
    );
    entity_save('user', $entity);
  }
}

/**
 * Set the renewal flag when a subscription is purchased
 *
 * @param object $account
 *   The user account to be granted the role
 * @param object $subscription
 *   The fully loaded node object of the subscription that was purchased
 * @param string $payment_type
 *   The payment type used to make the purchase
 */
function lb_subscription_set_renewal_flag($account, $subscription, $payment_type) {
  if ($payment_type == 'check') {
    $renew = 0;
  }
  else {
    $renew = 1;
  }
  // The $account that rules passes contains the original information, which may have
  // changed as a result of an action that has run.
  $entity = entity_load_single('user', $account->uid);
  $account_subscription_data = lb_subscription_retrieve_account_subscription_data($entity, $subscription);
  if ($account_subscription_data['delta'] === NULL) {
    lb_subscription_set_subscription($entity, $subscription);
    $entity = entity_load_single('user', $account->uid);
    $account_subscription_data = lb_subscription_retrieve_account_subscription_data($entity, $subscription);
  }
  if ($account_subscription_data['delta'] !== NULL) {
    if ($account_subscription_data['renew'] != $renew) {
      $entity->field_subscription[LANGUAGE_NONE][$account_subscription_data['delta']]['field_renew'] = array(
        LANGUAGE_NONE => array(
          0 => array(
            'value' => $renew,
          ),
        ),
      );
      entity_save('user', $entity);
    }
  }
}

/**
 * Revoke a role when a subscription expires
 *
 * @param object $account
 *   The user account to be granted the role
 * @param object $subscription
 *   The fully loaded node object of the expired subscription
 */
function lb_subscription_revoke_role($account, $subscription) {
  user_multiple_role_edit(array($account->uid), 'remove_role', $subscription->field_assign_role[LANGUAGE_NONE][0]['rid']);
}

/**
 * Remove a subscription when it expires
 *
 * @param object $account
 *   The user account to be granted the role
 * @param object $subscription
 *   The fully loaded node object of the expired subscription
 */
function lb_subscription_remove_subscription($account, $subscription) {
  $entity = entity_load_single('user', $account->uid);
  $account_subscription_data = lb_subscription_retrieve_account_subscription_data($account, $subscription);
  if ($account_subscription_data['delta'] !== NULL) {
    unset($entity->field_subscription[LANGUAGE_NONE][$account_subscription_data['delta']]);
    $entity->field_subscription[LANGUAGE_NONE] = array_values($entity->field_subscription[LANGUAGE_NONE]);
    entity_save('user', $entity);
  }
}
