<?php

require_once('include/studio.inc');

$drives = $studio->get_drives(true);

$studio->nav->header('Drives');

echo <<<HTML
<h1>Drives</h1>
<br/>
<table border=1>

HTML
;

foreach($drives as $drive) {
 echo <<<HTML
 <tr>
  <td>{$drive->letter}</td>
  <td>{$drive->type}</td>
 </tr>

HTML
  ;
}

echo <<<HTML
</table>

HTML
 ;


$studio->nav->footer();
