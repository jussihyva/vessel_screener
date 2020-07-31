const app = document.getElementById('app');

window.addEventListener('DOMContentLoaded', () => {
	const ws = new WebSocket('ws://localhost:8001/ws');
	ws.onopen = function(event) {
		console.log('WebSocket connection opened');
	}
	ws.onerror = function(error) {
		console.log(error);
	}
	ws.onmessage = function(event) {
		render(JSON.parse(event.data));
	}
});

function render(data) {
	var list = document.createElement('ul');
	data.forEach(elem => {
		const timestamp = elem['timestamp'];
		const name = elem['name'];
		const item = document.createElement('li');
		item.innerHTML = name + ' ' + timestamp;
		list.appendChild(item);
	});
	app.innerHTML = '';
	app.appendChild(list);
}
