const refreshInterval = 3000;

function openCountries(countryTable, myInterval, timeFilterSec)
{
	let current_page;

	updatePage_Country(countryTable, timeFilterSec);
	if (myInterval != null)
	{
		clearInterval(myInterval);
		myInterval = null;
	}
	myInterval = setInterval(updatePage_Country(countryTable, timeFilterSec), refreshInterval);
	current_page = 1;
	return(current_page);
}

function updatePage_Country(countryTable, timeFilterSec) {
	let timestamp = parseInt((Date.now() / 1000) - timeFilterSec, 10);
	fetch('/table_country?timestamp='+ timestamp)
	.then((res) => {
		return res.text();
	})
	.then((text) => {
		countryTable.innerHTML = text;
	});
}

export { openCountries, updatePage_Country };
