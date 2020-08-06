<?php

//ini_set('display_errors','On');

$frog_dir = $_SERVER['DOCUMENT_ROOT'] . '/include/frog';
require_once($frog_dir . '/frog.inc');

require_once('studio_class.inc');

$studio = new studio_class();
$studio->name = 'studio';

require_once('config.inc');

$studio->include_dir = dirname(__FILE__);

$cred = trim(file_get_contents($studio->data_dir . '/cred.txt'));
$studio->connect('studio',$cred,'studio');
$cred = '';

$studio->video_dir           = $studio->data_dir . "/videos";

$studio->register('uni');
$studio->register('course');
$studio->register('video');

$studio->html = new frog_html($studio);
$studio->nav  = new frog_navigator($studio);

?>
