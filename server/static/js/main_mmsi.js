const refreshInterval = 5000;

function openMMSI_List(countryTable, messageStatisticsTable, myInterval, timeFilterSec)
{
	let current_page;

	current_page = 2;
	updatePage_MMSI(countryTable, messageStatisticsTable, timeFilterSec);
	if (myInterval != null)
	{
		clearInterval(myInterval);
		myInterval = null;
	}
	myInterval = setInterval(function() {updatePage_MMSI(countryTable, messageStatisticsTable, timeFilterSec);}, refreshInterval);
	current_page = 2;
	return([current_page, myInterval]);
}

function updatePage_MMSI(countryTable, messageStatisticsTable, timeFilterSec) {
	let timestamp = parseInt((Date.now() / 1000) - timeFilterSec, 10);
	fetch('/table_mmsi?timestamp='+ timestamp)
	.then((res) => {
		return res.text()
	})
	.then((text) => {
		countryTable.innerHTML = text;
	})
	fetch('/table_message_statistics?timestamp='+ timestamp)
	.then((res) => {
		return res.text();
	})
	.then((text) => {
		messageStatisticsTable.innerHTML = text;
	});
}

export { openMMSI_List, updatePage_MMSI };
