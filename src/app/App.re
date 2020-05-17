[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";

let arrayContains = (value: 'a, array: array('a)) =>
  array |> Array.fold_left((found, elem) => found || elem == value, false);

let removeValue = (value: 'a, array: array('a)) =>
  Belt.Array.keep(array, item => item != value);

let addValue = (value: 'a, array: array('a)) =>
  Belt.Array.concat([|value|], array);

type state = {
  unwatchedVideos: array(Video.t),
  watchedVideos: array(Video.t),
  currentVideo: option(Video.t),
};

type action =
  | SelectVideo(Video.t)
  | ToggleWatched(Video.t)
  | SetVideos(array(Video.t));

let initialState = {
  unwatchedVideos: [||],
  watchedVideos: [||],
  currentVideo: None,
};

let reducer = (state, action) => {
  switch (action) {
  | SelectVideo(video) => {...state, currentVideo: Some(video)}
  | ToggleWatched(video) =>
    state.watchedVideos |> arrayContains(video)
      ? {
        ...state,
        unwatchedVideos: state.unwatchedVideos |> addValue(video),
        watchedVideos: state.watchedVideos |> removeValue(video),
      }
      : {
        ...state,
        unwatchedVideos: state.unwatchedVideos |> removeValue(video),
        watchedVideos: state.watchedVideos |> addValue(video),
      }
  | SetVideos(videos) => {
      ...state,
      unwatchedVideos: videos,
      watchedVideos: [||],
    }
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  React.useEffect0(() => {
    Js.Promise.(
      fetch(
        "https://my-json-server.typicode.com/kotlin-hands-on/kotlinconf-json/videos",
      )
      |> then_(response => response##json())
      |> then_(jsonResponse => {
           Js.log(jsonResponse);
           dispatch(SetVideos(jsonResponse));
           Js.Promise.resolve();
         })
      |> catch(_err => {
           Js.log("Failed to fetch videos");
           Js.Promise.resolve();
         })
      |> ignore
    );
    None;
  });

  <div>
    <h1> {React.string("KotlinConf Explorer")} </h1>
    <div>
      <h3> {React.string("Videos to watch")} </h3>
      <VideoList
        videos={state.unwatchedVideos}
        selectedVideo={state.currentVideo}
        onSelectVideo={video => dispatch(SelectVideo(video))}
      />
      <h3> {React.string("Watched videos")} </h3>
      <VideoList
        videos={state.watchedVideos}
        selectedVideo={state.currentVideo}
        onSelectVideo={video => dispatch(SelectVideo(video))}
      />
    </div>
    {switch (state.currentVideo) {
     | Some(video) =>
       <VideoPlayer
         video
         watchedVideo={state.watchedVideos |> arrayContains(video)}
         watchedButtonHandler={_ => dispatch(ToggleWatched(video))}
       />
     | None => React.null
     }}
  </div>;
};