const fs = require('fs');
const dictFile = "dict.txt";
const textFile = "file.txt";
const numTopOccurrences = 3;

/**
 *  Asynchronous function that reads a file.
 *  The returned promise attempts to read the file.
 *  If the read is successful, it calls the `fulfill' callback and passes an
 *      array of lines.
 *  If the read is unsuccessful, it calls the `reject' callback and passes
 *      the error.
 *
 *  @param fname The file to read
 *  @return A promise that reads the file
 *
 *  See "MDN Javascript Promise" and "Node.js FS module" for more details
 */
function readFile(fname) {
	return new Promise(
		(fulfill, reject) => {
			fs.readFile(fname, (err, data) => {
				if (err) {
					reject(err);
				} else {
					fulfill(data.toString().split('\n').filter(line => {
							return line.trim().length > 0;
						})
					);
				}
			});
		}
	);
}

/**
 *  This function sorts an array of objects that associate a word and
 *  the number of times it has occurred.
 *      [ { word: '<word>', count: <count> }, ... ]
 *
 *  @param arr The array of objects to sort
 *  @return The array sorted first by count, then alphabetically
 *
 *  See "MDN Javascript Array Sort" for more details
 */
function sortByCount(arr) {
	arr.sort((a, b) => {
		if (b.count > a.count) return 1;
		if (b.count < a.count) return -1;
		if (b.word > a.word) return 1;
		if (b.word < a.word) return -1;
		return 0;
	});

	return arr;
}

/**
 *  This function formats an array of objects in the form:
 *      [ { word: '<word>', count: <count> }, ... ]
 *  into a string that is displayable in the form:
 *      "<word> (<count>), <word> (<count>), ..."
 *
 *  @param occurrences An array of objects in the form above
 *  @return The displayable string
 *
 *  It returns the displayable string.
 *  See "MDN Javascript Array Join" for more details
 */
function printFormat(occurrences) {
	let strs = [];
	for (let occurrence of occurrences)
		strs.push(occurrence.word + " (" + occurrence.count + ")");
	return strs.join(", ");
}

/**
 *  This function gets the total number of words in a file
 *  It sums up the number of words per line.
 *
 *  @param text An array of lines in the file
 *  @return The total number of words
 *
 *  See "MDN Javascript Array Split" for more details
 */
function getTotalNumberOfWords(text) {
	let wordCount = 0;
	for (let line of text)
		wordCount += line.split(" ").length;
	return wordCount;
}

/**
 *  This function gets the top `num' word occurrences in a file
 *
 *  @param text An array of lines in the file
 *  @param num The number of top occurrences to return
 *  @return The sorted top word occurrences
 *
 *  See "MDN Javascript Object", "MDN Javascript Array Push",
 *    "MDN Javascript Array Splice" for more details
 */
function getTopWordOccurrences(text, num) {
	let wordMap = {};
	for (let line of text) {
		for (let word of line.split(" ")) {
			if (!(word in wordMap))
				wordMap[word] = 0;
			wordMap[word]++;
		}
	}

	let sortWordMap = [];
	for (let word in wordMap) {
		sortWordMap.push({
			word: word,
			count: wordMap[word]
		});
	}

	return sortByCount(sortWordMap).slice(0, num);
}

/**
 *  This function gets the misspelled words in a file based on a dictionary
 *
 *  @param text An array of lines in the file
 *  @param dict An array of words in the dictionary
 *  @return The misspelled words in the order they were found
 *
 *  See "MDN Javascript Array indexOf" for more details
 */
function getMisspelledWords(text, dict) {
	let misspelledWords = [];
	for (let line of text)
		for (let word of line.split(" "))
			if (dict.indexOf(word) === -1)
				misspelledWords.push(word);
	return misspelledWords;
}

/**
 *  Write this function, which takes a file (an array of lines), and applies
 *  a function, passed as a parameter, to each word. In other words, this function
 *  calls the function `fn` for every word in the file, with that word passed as
 *  the argument to fn. Then use this function in the remaining functions.
 *
 *  @param text An array of lines of text from a file
 *  @param fn The function to call with every word from the file passed as its only parameter
 */
function forEachWord(text, fn) {
	// TODO: implement this function
	
	for (let line of text)
		for (let word of line.split(" "))
			fn(word);
	
	
}

/**
 *  This function returns all words in `text` (an array of lines of a file) that
 *  are of length `length`. You can use the string length property, i.e.
 *     let str = "hello";
 *     console.log(str.length); // 5
 *
 *  You must use the function "forEachWord".
 *
 *  @param text An array of lines in the file
 *  @param length The length of the words you want to find
 *  @return An array of words of length `length`
 *
 */


function wordsOfLength(text, length) {
	let words = [];
	// TODO: implement this function
	
	forEachWord(text, (a) => {if(a.length === length) {words.push(a);} });
		
	return words;
}




/**
 *  Find all words that are palindromes (https://en.wikipedia.org/wiki/Palindrome)
 *  in the file text.
 *
 *  You must use the function "forEachWord".
 *
 *  @param text An array of lines in the file
 *  @return An array of palindromes
 */
function isPalindrome(word) {
	let flag = true;

	for(var i = 0; i < word.length; i++) {
		if(word.charAt(i) != word.charAt(word.length-1-i))
			flag = false;
	}

	return flag;
}

function getPalindromes(text) {
	let palindromes = [];
	// TODO: implement this function
	
		forEachWord(text, (a) => {if(isPalindrome(a)) {palindromes.push(a);}});

	return palindromes;
}

/**
 *  This function does the task that is required for the project.
 *  Prints the total number of words, the average number of words per line,
 *    the top occurring words, and the misspelled words in a file.
 *
 *  @param text An array of lines in the file
 *  @param dict An array of words in the dictionary
 *
 *  See "MDN Javascript parseFloat" for more details
 */
function processResults(text, dict) {
	let totalWords = getTotalNumberOfWords(text);
	let averageWordsPerLine = totalWords / parseFloat(text.length);
	let topWordOccurrences = getTopWordOccurrences(text, numTopOccurrences);
	let misspelledWords = getMisspelledWords(text, dict);

	console.log("Total number of words:", totalWords);
	console.log("Average words per line:", averageWordsPerLine);
	console.log("Top occurrences:", printFormat(topWordOccurrences));
	console.log("Misspelled Words:", misspelledWords.join(", "));

	// TODO: call the functions you just wrote here on the `text` variable
	//		 don't forget to pass a length to the function `wordsOfLength`
	let wordsOfLengthThree = wordsOfLength(text, 3);
	let palindromeWords = getPalindromes(text);

	console.log("Words of length 3: ", wordsOfLengthThree);
	console.log("palindromeWords: ", palindromeWords);
}

/**
 *  Read the file and dictionary and only process them if they were
 *		successfully read.
 */
Promise.all([readFile(textFile), readFile(dictFile)]).then(files => {
	const text = files[0];
	const dict = files[1];
	processResults(text, dict);
}, error => {
	console.log("There was an error!", error.toString());
});
