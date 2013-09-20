The Commerce TaxCloud module enables your Drupal Commerce store to calculate
appropriate tax rates for the line items in a shopping cart using TaxCloud's
API.

-- REQUIREMENTS --

PHP-TaxCloud library - https://github.com/VeggieMeat/php-taxcloud

TaxCloud API ID and API Key.

(optional) USPS API Key.

-- INSTALLATION --

Install module as usual. See http://drupal.org/node/70151 for more information.

PHP-TaxCloud library should be installed to sites/all/libraries if using the
Libraries API. Alternatively, a composer.json file is included for use with
Composer Manager.

-- CONFIGURATION --

Configure basic settings at admin/commerce/config/taxes/taxcloud.

Configure Taxability Information Codes per line item type at
admin/commerce/config/taxes/taxcloud/line-items.
