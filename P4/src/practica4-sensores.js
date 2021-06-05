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

function actualizaciones() {
	socket.on("connect", ()=>{
		socket.emit("conexion", "sensores");
	});

	socket.on("actualizar-sistemas", (event) => {
		if (event.nombre == "Aire")
			$("#AC").html(event.valor);
		else if (event.nombre == "Calefaccion")
			$("#cal").html(event.valor);
		else if (event.nombre == "Persianas")
			$("#persianas").html(event.valor);
		else if (event.nombre == "Luces")
			$("#luces").html(event.valor);
	});
}

$(() =>{
	luminosidad();
	temperatura();
	actualizaciones();
});
