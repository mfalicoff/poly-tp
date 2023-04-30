<?php $host= gethostname();
$ip = gethostbyname($host);
echo "Hello I am a web server, ";
echo "Serveur : " . (string) $host . "  /  ";
echo "Mon ip : " . (string) $ip . "  /  ";
?>