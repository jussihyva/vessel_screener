const refreshInterval = 5000;

function openCountries(countryTable, messageStatisticsTable, myInterval, timeFilterSec)
{
	let current_page;

	updatePage_Country(countryTable, messageStatisticsTable, timeFilterSec);
	if (myInterval != null)
	{
		clearInterval(myInterval);
		myInterval = null;
	}
	myInterval = setInterval(function() {updatePage_Country(countryTable, messageStatisticsTable, timeFilterSec);}, refreshInterval);
	current_page = 1;
	return([current_page, myInterval]);
}

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

export { openCountries, updatePage_Country };
