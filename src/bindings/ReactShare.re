module Telegram = {
  [@bs.module "react-share"] [@react.component]
  external make: (~url: string, ~children: React.element) => React.element =
    "TelegramShareButton";

  module Icon = {
    [@bs.module "react-share"] [@react.component]
    external make: (~size: int, ~round: bool) => React.element =
      "TelegramIcon";
  };
};

module Reddit = {
  [@bs.module "react-share"] [@react.component]
  external make: (~url: string, ~children: React.element) => React.element =
    "RedditShareButton";

  module Icon = {
    [@bs.module "react-share"] [@react.component]
    external make: (~size: int, ~round: bool) => React.element = "RedditIcon";
  };
};