import "/node_modules/jquery/dist/jquery.min.js";
import "/socket.io/socket.io.js";

const URL = document.URL.substring(0, document.URL.lastIndexOf("/"));
const socket = io.connect(URL);

function AC () {
	var boton = $("#AC");

	boton.on("click", () => {
		if(boton.text() == "Encender") {
			socket.emit("sistemas", {nombre: "Aire", valor: "encendido"});
			socket.emit("accion-usuario", {nombre: "Aire", valor: "encendido"});
		}
		else if (boton.text() == "Apagar"){
			socket.emit("sistemas", {nombre: "Aire", valor: "apagado"});
			socket.emit("accion-usuario", {nombre: "Aire", valor: "apagado"});
		}
	});
}

function calefaccion () {
	var boton = $("#cal");

	boton.on("click", () => {
		if(boton.text() == "Encender") {
			socket.emit("sistemas", {nombre: "Calefaccion", valor: "encendida"});
			socket.emit("accion-usuario", {nombre: "Calefaccion", valor: "encendida"});
		}
		else if (boton.text() == "Apagar"){
			socket.emit("sistemas", {nombre: "Calefaccion", valor: "apagada"});
			socket.emit("accion-usuario", {nombre: "Calefaccion", valor: "apagada"});
		}
	});
}

function persianas() {
	var boton = $("#persianas");

	boton.on("click", () => {
		if(boton.text() == "Bajar") {
			socket.emit("sistemas", {nombre: "Persianas", valor: "bajadas"});
			socket.emit("accion-usuario", {nombre: "Persianas", valor: "bajadas"});
		}
		else {
			socket.emit("sistemas", {nombre: "Persianas", valor:"subidas"});
			socket.emit("accion-usuario", {nombre: "Persianas", valor:"subidas"});
		}
	});
}

function luces() {
	var boton = $("#luces");

	boton.on("click", () => {
		if(boton.text() == "Encender") {
			socket.emit("sistemas", {nombre: "Luces", valor: "encendidas"});
			socket.emit("accion-usuario", {nombre: "Luces", valor: "encendidas"});
		}
		else {
			socket.emit("sistemas", {nombre: "Luces", valor:"apagadas"});
			socket.emit("accion-usuario", {nombre: "Luces", valor:"apagadas"});
		}
	});
}

function actualizaciones () {
	socket.on("connect", ()=>{
		socket.emit("conexion", "cliente");
	});

	socket.on("actualizar-sensores", (event) => {
		if(event.nombre == "Temperatura")
			$("#temperatura").text(event.valor);
		else if (event.nombre == "Luminosidad")
			$("#nivel-lum").text(event.valor);
	});

	socket.on("actualizar-sistemas", (event) => {
		if (event.nombre == "Aire") {
			var boton = $("#AC");
			if (event.valor == "encendido")
				boton.html("Apagar");
			else
				boton.html("Encender")
		}
		else if (event.nombre == "Calefaccion") {
			var boton = $("#cal");
			if (event.valor == "encendida")
				boton.html("Apagar");
			else
				boton.html("Encender")
		}
		else if (event.nombre == "Persianas") {
			var boton = $("#persianas");
			if (event.valor == "bajadas")
				boton.html("Subir");
			else
				boton.html("Bajar")
		}
		else if (event.nombre == "Luces") {
			var boton = $("#luces");
			if (event.valor == "encendidas")
				boton.html("Apagar");
			else
				boton.html("Encender")
		}
	});

	socket.on("recibir-alerta", (alerta) => {
		if (alerta.nombre == "Aire")
			alert("Se ha encendido el aire acondicionado por sobrepasar los: " + alerta.valor + "º");
		else if (alerta.nombre == "Calefaccion")
			alert("Se ha encendido la calefacción porque hay menos de: " + alerta.valor + "º");
		else if (alerta.nombre == "Persianas")
			alert("Se han bajado las persianas porque fuera hay poca luz")
		else if (alerta.nombre == "Luces")
			alert("Se han encendido porque fuera hay poca luz")
	});

}

$(() => {
	AC();
	calefaccion()
	persianas();
	luces();
	actualizaciones();
});
