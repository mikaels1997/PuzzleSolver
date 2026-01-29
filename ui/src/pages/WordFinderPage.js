import WordFinderButtons from "components/wordfinder/WordFinderButtons";
import WordFinderGrid from "components/wordfinder/WordFinderGrid";
import WordResultContainer from "components/wordfinder/WordResultContainer";
import WordFinderState from "stores/WordFinderState";

const wordFinderState = new WordFinderState();

const WordFinderPage = () => {
  return <div className="word-finder-main">
    <h2>WORD FINDER</h2>
    <div className="word-finder-view">
      <WordFinderGrid state={wordFinderState}/>
      <WordFinderButtons state={wordFinderState}/>
      <WordResultContainer state={wordFinderState}/>
    </div>
  </div>
};

export default WordFinderPage;