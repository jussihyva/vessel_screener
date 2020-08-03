
window.addEventListener('DOMContentLoaded', () => {
	const app = document.getElementById('app');
	const ws = new WebSocket('ws://localhost:8001/ws');
	ws.onopen = function(event) {
		console.log('WebSocket connection opened');
	}
	ws.onerror = function(error) {
		console.log(error);
	}
	ws.onmessage = function(event) {
		render(app, JSON.parse(event.data));
	}
});

function render(container, data) {
	var list = document.createElement('ul');
	data.forEach(elem => {
		const timestamp = elem['timestamp'];
		const name = elem['name'];
		const lat = elem['lat'];
		const lon = elem['lon'];
		const item = document.createElement('li');
		item.appendChild(createMapLink(name, lat, lon));
		list.appendChild(item);
	});
	container.innerHTML = '';
	container.appendChild(list);
}

function createMapLink(name, lat, lon) {
	const a = document.createElement('a');
	const text = document.createTextNode(name);
	a.appendChild(text);
	a.target = '_blank';
	a.href = `https://www.google.com/maps/search/?api=1&query=${lat},${lon}`;
	return a;
}
