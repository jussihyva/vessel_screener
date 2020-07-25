
let filterTime = 900;
const timeFilterElem = document.getElementById("time_period");


$(document).ready(function () {
	setInterval(function () { update_page(); }, 3000);
	$("#add_mmsi_mid").click(function () { $('#ui_modal').modal('show'); });
	$("#save").click(function () {
		let mmsi_mid = $("#mmsi_mid").val();
		let mmsi_mid_list = mmsi_mid.split("\n");
		for (var i = 0; i < mmsi_mid_list.length; ++i) {
			$.ajax(
				{
					url: "/country",
					type: "POST",
					contentType: "application/json",
					data: JSON.stringify({ "symbol": mmsi_mid_list[i] }),
					dataType: "json"
				})
		}
		$('#ui_modal').modal('dispose');
	});

	timeFilterElem.onchange = filterPeriod;
});

function filterPeriod() {
	filterTime = timeFilterElem.value;
	console.log('value changed', filterTime);
	update_page();
}

function update_page() {
	$.ajax(
		{
			url: "/table",
			type: "GET",
			data: { "timestamp": parseInt((Date.now() / 1000) - filterTime, 10) },
			success: function (data) {
				document.getElementById("country_table").innerHTML = data
			}
		})
}