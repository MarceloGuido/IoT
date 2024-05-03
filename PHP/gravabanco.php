<?php 

if(isset($_GET["botao"])) { 
   $botao = $_GET["botao"]; // le o valor do botao vindo no HTTP GET 
   $hora = $_GET["hora"];  	 
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

   $sql = "INSERT INTO tbl_satisfacao (botao, data_hora) VALUES ($botao,$hora)"; 

   if ($connection->query($sql) === TRUE) { 
      echo "Novo registro criado com sucesso!!!"; 
   } else { 
       echo "Erro: " . $sql . " => " . $connection->error; 
   } 
 
   $connection->close(); 
} else { 

   echo "botao nao informado na requisicao HTTP"; 
} 

//Código criado pelo grupo: Roberto, Sérgio, Kauan e Josicleide - 2023

?> 
