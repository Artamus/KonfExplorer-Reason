let backgroundColor = watched => if (watched) {"red"} else {"green"};
let buttonMessage = watched =>
  if (watched) {"Mark as unwatched"} else {"Mark as watched"};

let containerStyle =
  ReactDOMRe.Style.make(
    ~position="absolute",
    ~top="10px",
    ~right="10px",
    ~fontFamily="sans-serif",
    (),
  );

let buttonStyle = backgroundColor =>
  ReactDOMRe.Style.make(~display="block", ~backgroundColor, ());

let shareContainerStyle =
  ReactDOMRe.Style.make(~position="flex", ~marginBottom="10px", ());

[@react.component]
let make = (~video: Video.t, ~watchedVideo: bool, ~watchedButtonHandler) => {
  <div style=containerStyle>
    <h3> {React.string(video.speaker ++ ": " ++ video.title)} </h3>
    <button
      style={backgroundColor(watchedVideo)->buttonStyle}
      onClick={_ => watchedButtonHandler()}>
      {React.string(buttonMessage(watchedVideo))}
    </button>
    <div style=shareContainerStyle>
      <ReactShare.Telegram url={video.videoUrl}>
        <ReactShare.Telegram.Icon size=32 round=true />
      </ReactShare.Telegram>
      <ReactShare.Reddit url={video.videoUrl}>
        <ReactShare.Reddit.Icon size=32 round=false />
      </ReactShare.Reddit>
    </div>
    <ReactPlayer url={video.videoUrl} />
  </div>;
};