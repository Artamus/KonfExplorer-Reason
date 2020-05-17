let formatVideo = (video: Video.t, selectedVideo: option(Video.t)) => {
  let prefix =
    switch (selectedVideo) {
    | None => ""
    | Some(selected) => video == selected ? "> " : ""
    };

  prefix ++ video.speaker ++ ": " ++ video.title;
};

[@react.component]
let make =
    (
      ~videos: array(Video.t),
      ~selectedVideo: option(Video.t),
      ~onSelectVideo,
    ) => {
  <div>
    {videos
     ->Belt.Array.map(video =>
         <p
           key={string_of_int(video.id)} onClick={_ => onSelectVideo(video)}>
           {video->formatVideo(selectedVideo)->React.string}
         </p>
       )
     ->React.array}
  </div>;
};