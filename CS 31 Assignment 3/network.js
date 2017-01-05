const http = require('http');

/**
 *  The function asynchronously fetches a random "secret" string using an http
 *  request. After it gets the response, it parses it to get the secret.
 *  Once this function gets the secret, it calls the function passed as "callback"
 *  with its only argument being the secret.
 *
 *  @param callback The function to call after the secret is received.
 *                    Its only argument is the secret phrase
 */
function getSecret(callback) {
	http.get({
		host: 'www.randomtext.me',
		path: '/api/gibberish/p-1/70-120'
	}, (response) => {
		let str = "";

		response.on('data', (chunk) => {
			str += chunk;
		});

		response.on('end', () => {
			try {
				let json = JSON.parse(str);
				callback(json.text_out.replace("<p>","").replace("</p>","").replace("\\r","").replace(/[^a-zA-Z\s]/g, "").toLowerCase());
				console.log(str);
			} catch (e) {
				console.log(e);
				callback("default secret");
			}
		});
	}).end();
}

/**
 *  Gets a "secret" and determines whether is it "nice".
 *
 *  The "secret" is a string sequence of random space-separated words with only
 *  lowercase letters and no punctuation (similar to exercise during Session 3)
 *  You may make the same assumptions about the "secret" as we did about file.txt
 *  during Session 3.
 *  examples:
 *      "this is what a secret looks like"
 *      "combination pajama wallet hairy let a fridge light up"
 *
 *  To get the secret, you must call the `getSecret` function. You must pass it
 *  a callback that accepts one argument -- the secret, a randomly generated string
 *  that will be passed to your callback. The callback you write will parse the
 *  "secret" it is passed and determine if it is "nice".
 *
 *  A secret is "nice" if all of the following are TRUE:
 *    - The number of words with odd length < the number of words with even length
 *    - The letter "x" does NOT appear in the secret
 *    - The total number of words with 2 or less letters is < 20% of the total number of words
 *
 *  If these conditions are met, it should print out "The secret is NICE!"
 *  Otherwise it should print out the FIRST condition the secret did not meet.
 *
 *  You can, write auxiliary (helper) functions.
 *  You can use the Session 3's slides as reference.
 *  You can use code from Session 3's solution as a reference.
 *  You can also search the Mozilla Developer Network for JavaScript built-in
 *  functions and properties that might be useful, like split() or length.
 *
 *  Lastly, if you're having trouble, try putting some console.log() statements
 *  that print various things in various places related to the problem you're having
 *  to see exactly what's going on. This will help you narrow down the problem.
 *
 *  Here are some examples of how this function should behave:
 *
 *  secret="javascript is more confusing than life"
 *      output: The secret is NICE!
 *
 *  secret="to be or not to be that is the question"
 *      output: The secret has more than 20% words with two or less letters.
 *
 *  secret="the cat ran far from the xylophone"
 *      output: There are more odd-length words than even-length words.
 *
 *  secret="my rabbit is cuter than an ox"
 *      output: The secret contains the letter 'x'.
 */
function moreEvenThanOdd(s) {
	let countEven = 0;
	let countOdd = 0;
	let words = [];

	for(let word of s.split(" "))
		words.push(word);

	for(let word of words){
		if(word.length % 2 ===0)
			countEven++;
		else
			countOdd++;
	}
	//console.log("moreEvenThanOdd: ");
	//console.log(countEven > countOdd);

	return countEven > countOdd;
}

function doesNotContainX(s) {
	//console.log("doesNotContainX");
	//console.log(s.indexOf('x') === -1);
	return s.indexOf('x') === -1;
}

function twoOrLessLetterWordsLessThanTwentyPercent(s){
	
	let countTwoOrLessLetterWords = 0;

	let words = [];
	for(let word of s.split(" "))
		words.push(word);

	for(word of words) {
		if(word.length < 3)
			countTwoOrLessLetterWords++;
	}
	//console.log("twoOrLessLetterWordsLessThanTwentyPercent: ");
	//console.log(countTwoOrLessLetterWords / words.length < 0.2);
	return countTwoOrLessLetterWords / words.length < 0.2;

}



function isNiceSecret(s) {
	/*
	console.log(moreEvenThanOdd(s));
	console.log(doesNotContainX(s));
	console.log(twoOrLessLetterWordsLessThanTwentyPercent(s));

	console.log(!(moreEvenThanOdd(s) || doesNotContainX(s) || twoOrLessLetterWordsLessThanTwentyPercent(s)));
	*/
	// TODO: implement
	return !(moreEvenThanOdd(s) || doesNotContainX(s) || twoOrLessLetterWordsLessThanTwentyPercent(s));

}

getSecret(isNiceSecret);
