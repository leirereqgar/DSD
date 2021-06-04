import "/node_modules/jquery/dist/jquery.min.js";
import "/socket.io/socket.io.js";

const URL = document.URL.substring(0, document.URL.lastIndexOf("/"));
const socket = io.connect(URL);

function luminosidad() {
	var lum = $("#lum");
	lum.on("input", function() {
		socket.emit("sensores", {
				nombre: "Luminosidad",
				valor: Number(this.value)
		});
	});
}

function temperatura() {
	var grados = $("#grados");
	grados.on("input", function() {
		socket.emit("sensores", {
				nombre: "Temperatura",
				valor: Number(this.value)
		});
	});
}

function iniciarConexion() {
	socket.on("connect", ()=>{
		socket.emit("conexion", "sensores");
	});

	socket.on("dispositivos", (tipo) => {
		if (tipo.nombre == "Aire acondicionado") {
			var estado = $("#AC");

			if(tipo.value == "encendido")
				estado.text("encendido");
			else
				estado.text("apagado");
		}
		else if (tipo.nombre == "Persianas") {
			var estado = $("#persianas");

			if(tipo.value == "subidas")
				estado.text("subidas");
			else
				estado.text("bajadas");
		}
		else if (tipo.nombre == "Luces") {
			var estado = $("#luces");

			if(tipo.value == "encendidas")
				estado.text("encendidas");
			else
				estado.text("apagadas");
		}
	})
}

$(() =>{
	luminosidad();
	temperatura();
	iniciarConexion();
});
