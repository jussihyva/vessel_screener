function updatePage_Country(countryTable, messageStatisticsTable, timeFilterSec) {
	let timestamp = parseInt((Date.now() / 1000) - timeFilterSec, 10);
	fetch('/table_country?timestamp='+ timestamp)
	.then((res) => {
		return res.text();
	})
	.then((text) => {
		countryTable.innerHTML = text;
	});
	fetch('/table_message_statistics?timestamp='+ timestamp)
	.then((res) => {
		return res.text();
	})
	.then((text) => {
		messageStatisticsTable.innerHTML = text;
	});
}

export { updatePage_Country };
