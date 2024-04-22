<?php

if(isset($_GET["temperatura"])) {
   $temperatura = $_GET["temperatura"]; // le o valor da temperatura vindo no HTTP GET

   $servername = "localhost";
   $username = "etec";
   $password = "3tec*IOT";
   $database_name = "db_iot";

   // Cria a conexao MySQL a partir do PHP para o servidor MySQL
   $connection = new mysqli($servername, $username, $password, $database_name);
   // Verifica a conexao
   if ($connection->connect_error) {
      die("Conexao com o MySQL falhou: " . $connection->connect_error);
   }
  
   $sql = "INSERT INTO tbl_DHT11 (temperatura) VALUES ($temperatura)";

   if ($connection->query($sql) === TRUE) {
      echo "Novo registro criado com sucesso!!!";
   } else {
      echo "Erro: " . $sql . " => " . $connection->error;
   }

   $connection->close();
} else {
   echo "temperatura nao informada na requisicao HTTP";
}
?>
