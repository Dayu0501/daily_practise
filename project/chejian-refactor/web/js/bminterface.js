function randnum() {
    return parseInt(Math.floor(Math.random() * 1000));
}

function bm_html(id, msg) {
    $("#" + id).html(msg);
}

function getNum(inByte) {
    switch (inByte) {
        case '!': return 33;
        case '"': return 34;
        case '#': return 35;
        case '$': return 36;
        case '%': return 37;
        case '&': return 38;
        case '\'': return 39;
        case '(': return 40;
        case ')': return 41;
        case '*': return 42;
        case '+': return 43;
        case ',': return 44;
        case '-': return 45;
        case '.': return 46;
        case '/': return 47;
        case '0': return 48;
        case '1': return 49;
        case '2': return 50;
        case '3': return 51;
        case '4': return 52;
        case '5': return 53;
        case '6': return 54;
        case '7': return 55;
        case '8': return 56;
        case '9': return 57;
        case ':': return 58;
        case ';': return 59;
        case '<': return 60;
        case '=': return 61;
        case '>': return 62;
        case '?': return 63;
        case '@': return 64;
        case 'A': return 65;
        case 'B': return 66;
        case 'C': return 67;
        case 'D': return 68;
        case 'E': return 69;
        case 'F': return 70;
        case 'G': return 71;
        case 'H': return 72;
        case 'I': return 73;
        case 'J': return 74;
        case 'K': return 75;
        case 'L': return 76;
        case 'M': return 77;
        case 'N': return 78;
        case 'O': return 79;
        case 'P': return 80;
        case 'Q': return 81;
        case 'R': return 82;
        case 'S': return 83;
        case 'T': return 84;
        case 'U': return 85;
        case 'V': return 86;
        case 'W': return 87;
        case 'X': return 88;
        case 'Y': return 89;
        case 'Z': return 90;
        case '[': return 91;
        case '\\': return 92;
        case ']': return 93;
        case '^': return 94;
        case '_': return 95;
        case '`': return 96;
        case 'a': return 97;
        case 'b': return 98;
        case 'c': return 99;
        case 'd': return 100;
        case 'e': return 101;
        case 'f': return 102;
        case 'g': return 103;
        case 'h': return 104;
        case 'i': return 105;
        case 'j': return 106;
        case 'k': return 107;
        case 'l': return 108;
        case 'm': return 109;
        case 'n': return 110;
        case 'o': return 111;
        case 'p': return 112;
        case 'q': return 113;
        case 'r': return 114;
        case 's': return 115;
        case 't': return 116;
        case 'u': return 117;
        case 'v': return 118;
        case 'w': return 119;
        case 'x': return 120;
        case 'y': return 121;
        case 'z': return 122;
        case '{': return 123;
        case '|': return 124;
        case '}': return 125;
        case '~': return 126;

    }

    return Number(inByte);
}

function getByte(inNum) {
    switch (inNum) {
        case 33: return '!';
        case 34: return '"';
        case 35: return '#';
        case 36: return '$';
        case 37: return '%';
        case 38: return '&';
        case 39: return '\'';
        case 40: return '(';
        case 41: return ')';
        case 42: return '*';
        case 43: return '+';
        case 44: return ',';
        case 45: return '-';
        case 46: return '.';
        case 47: return '/';
        case 48: return '0';
        case 49: return '1';
        case 50: return '2';
        case 51: return '3';
        case 52: return '4';
        case 53: return '5';
        case 54: return '6';
        case 55: return '7';
        case 56: return '8';
        case 57: return '9';
        case 58: return ':';
        case 59: return ';';
        case 60: return '<';
        case 61: return '=';
        case 62: return '>';
        case 63: return '?';
        case 64: return '@';
        case 65: return 'A';
        case 66: return 'B';
        case 67: return 'C';
        case 68: return 'D';
        case 69: return 'E';
        case 70: return 'F';
        case 71: return 'G';
        case 72: return 'H';
        case 73: return 'I';
        case 74: return 'J';
        case 75: return 'K';
        case 76: return 'L';
        case 77: return 'M';
        case 78: return 'N';
        case 79: return 'O';
        case 80: return 'P';
        case 81: return 'Q';
        case 82: return 'R';
        case 83: return 'S';
        case 84: return 'T';
        case 85: return 'U';
        case 86: return 'V';
        case 87: return 'W';
        case 88: return 'X';
        case 89: return 'Y';
        case 90: return 'Z';
        case 91: return '[';
        case 92: return '\\';
        case 93: return ']';
        case 94: return '^';
        case 95: return '_';
        case 96: return '`';
        case 97: return 'a';
        case 98: return 'b';
        case 99: return 'c';
        case 100: return 'd';
        case 101: return 'e';
        case 102: return 'f';
        case 103: return 'g';
        case 104: return 'h';
        case 105: return 'i';
        case 106: return 'j';
        case 107: return 'k';
        case 108: return 'l';
        case 109: return 'm';
        case 110: return 'n';
        case 111: return 'o';
        case 112: return 'p';
        case 113: return 'q';
        case 114: return 'r';
        case 115: return 's';
        case 116: return 't';
        case 117: return 'u';
        case 118: return 'v';
        case 119: return 'w';
        case 120: return 'x';
        case 121: return 'y';
        case 122: return 'z';
        case 123: return '{';
        case 124: return '|';
        case 125: return '}';
        case 126: return '~';

    }

    return "";
}

   


function mkpwd(pwd, key) {
    var retpwd="";
    var subKey = key % 9 + 1;
    for (var i = 0; i < pwd.length; i++) {
        var c = getNum(pwd.charAt(i));
        if (128 - c > subKey) {
            c = c + subKey;
        }
        var strByte = getByte(c);
        if (strByte == '!'
            || strByte == '#'
            || strByte == '$'
            || strByte == '%'
            || strByte == '^'
            || strByte == '&'
            || strByte == '*'
        ) {
            c = c - subKey;
        }
        retpwd += getByte(c);
    }
    return retpwd;
}

function bm_ajax(action, extbuf, cb) {

    var randid = randnum();
    var pwd = mkpwd(getCookie("pwd"), randid);

    $.ajax({
        url: "../cgi/" + action + "?randid=" + randid + "&pwd=" + pwd + extbuf,
        type: "post",
        processData: false,
        contentType: false,
        done: function (res) {
            console.log("done" + res);
        },
        success: function (res) {
            if (res) {
                cb(res);
            }
        },
        error: function (err) {
            cb(JSON.parse("[{\"id\":\"return\",\"value\":\"false\"}]"));
        }
    });
    return true;
}

function bm_slave_ajax(slaveip, action, id, extbuf, cb) {
    var randid = randnum();
    var pwd = mkpwd(getCookie("pwd"), randid);

    $.ajax({
        url: "http://" + slaveip + ":10080/cgi/" + action + "?randid=" + randid + "&pwd=" + pwd + extbuf,
        type: "post",
        processData: false,
        contentType: false,
        done: function (res) {
            console.log("done" + res);
        },
        success: function (res) {
            if (res) {
                cb(id,res);
            }
        },
        error: function (err) {
            cb(-1,JSON.parse("[{\"id\":\"return\",\"value\":\"false\"}]"));
        },
        returnID:id
    });
    return true;
}

function bm_cgi(action, param, cb) {
    bm_ajax(action, param, function (json) {
        console.log(json);
        if (json["return"]) {
            if (json["value"]) {
                cb(json["value"]);
            } else {
                cb();
            }
        }
    });
}

function bm_getEditCheckBoxHtml(name, id, value) {
    var html = "";
    html += "<div class=\"form-group\">";
    html += "<label for=\"firstname\" class=\"col-sm-3 control-label\">" + name + ":</label>";
    html += "<div class=\"col-sm-8\">";
    if (value)
        html += "<input type=\"checkbox\" id=\"" + id + "\" style=\"padding-top:5px;\" checked>";
    else
        html += "<input type=\"checkbox\"  id=\"" + id + "\" style=\"padding-top:5px;\">";

    html += "</div>";
    html += "</div>";
    return html;
}

function bm_getEditInputHtml(name, id, placeholder, value) {
    var html = "";
    html += "<div class=\"form-group\">";
    html += "<label for=\"firstname\" class=\"col-sm-3 control-label\">" + name + ":</label>";
    html += "<div class=\"col-sm-8\">";
    html += "<input type=\"text\" class=\"form-control\" id=\"" + id + "\" placeholder=\"" + placeholder + "\" value=\"" + value + "\">";
    html += "</div>";
    html += "</div>";
    return html;
}

function bm_getEditShortInputHtml(name, id, placeholder, value) {
    var html = "";
    html += "<div class=\"form-group\">";
    html += "<label for=\"firstname\" class=\"col-sm-3 control-label\">" + name + ":</label>";
    html += "<div class=\"col-sm-8\">";
    html += "<input type=\"text\" class=\"form-control\" id=\"" + id + "\" placeholder=\"" + placeholder + "\" value=\"" + value + "\">";
    html += "</div>";
    html += "</div>";
    return html;
}

function bm_getEditHtmlByJson(json,shortInput) {
    var html = "";
    for (var key in json) {
        console.log("key:" + key + " json[key]" + json[key]);
        if (typeof json[key] == "boolean") {
            html += bm_getEditCheckBoxHtml(key, key, json[key]);
        }
        else {
            if (shortInput) {
                html += bm_getEditShortInputHtml(key, key, json[key], json[key]);
            } else
            {
                html += bm_getEditInputHtml(key, key, json[key], json[key]);

            }    
        }
    }
    return html;
}

function bm_getInputHtml(id, value, isHidden) {
    var html = "";
    var styleData = "";
    if (isHidden) {
        styleData = "hidden";
    } else {
        styleData = "class=\"form-control\"";
    }

    html += "<input type=\"text\" " + styleData + " id=\"" + id + "\" value=\"" + value + "\">";

    return html;
}

function bm_setInpuUnable(id) {
    if ($("#" + id)) {
        var aa = $("#" + id).attr("type");
        if ($("#" + id).attr("type") == "text") {
            $("#" + id).attr("readonly", "readonly");
        } else if ($("#" + id).attr("type") == "checkbox") {
            $("#" + id).attr("onclick", "return false;");
        }
    }
}

function successMsg(msg) {
    bm_html("div_MsgOut", "<div class=\"alert alert-success\" style=\"max-width:400px\" >" + msg + "</div >");
}
function dangerMsg(msg) {
    bm_html("div_MsgOut", "<div class=\"alert alert-danger\" style=\"max-width:400px\" >" + msg + "</div >");
}

function clearMsg() {
    bm_html("div_MsgOut", "");
}

function setCookie(name, value) {
    var Days = 30;
    var exp = new Date();
    exp.setTime(exp.getTime() + Days * 24 * 60 * 60 * 1000);
    document.cookie = name + "=" + escape(value) + ";expires=" + exp.toGMTString();
}

function getCookie(name) {
    var arr, reg = new RegExp("(^| )" + name + "=([^;]*)(;|$)");
    if (arr = document.cookie.match(reg))
        return unescape(arr[2]);
    else
        return null;
}

function delCookie(name) {
    var exp = new Date();
    exp.setTime(exp.getTime() - 1);
    var cval = getCookie(name);
    if (cval != null)
        document.cookie = name + "=" + cval + ";expires=" + exp.toGMTString();
}

function eventStop(ev) {
    ev.stopPropagation();
}

function loadJsonHtml(thead_id, tbody_id, json, eventJson) {
    var thead_str = "";
    var tbody_str = "";

    if (json) {
        var OrderDara = json["order"];
        var VectorData = json["value"];

        if (OrderDara && VectorData) {
            thead_str += "<tr>"
            for (var i = 0; i < OrderDara.length; i++) {
                thead_str += "<th>" + OrderDara[i]["name"] + "</th>";
            }
            if (eventJson && eventJson["td_event"]) {
                thead_str += "<th>²Ù×÷</th>";
            }
            thead_str += "</tr>"

            for (var i = 0; i < VectorData.length; i++) {
                var tr_onclick = "";
                if (eventJson && eventJson["tr_cbName"]) {
                    tr_onclick += " onclick =\"" + eventJson["tr_cbName"] + "(";
                    for (var j = 0; j < eventJson["tr_paramKeyList"].length; j++) {
                        if (j != 0)
                            tr_onclick += ",";
                        tr_onclick += "'" + VectorData[i][eventJson["tr_paramKeyList"][j]["paramKey"]] + "'";
                    }
                    tr_onclick += ")\"";
                }
                tbody_str += "<tr" + tr_onclick + ">"
                for (var j = 0; j < OrderDara.length; j++) {
                    tbody_str += "<td>" + VectorData[i][OrderDara[j]["name"]] + "</td>";
                }
                if (eventJson && eventJson["td_event"]) {
                    tbody_str += "<td>"
                    for (var j = 0; j < eventJson["td_event"].length; j++) {
                        var td_onclick = "";
                        if (eventJson && eventJson["td_event"][j]["cbName"]) {
                            td_onclick += " onclick =\"eventStop(event);" + eventJson["td_event"][j]["cbName"] + "(";
                            for (var z = 0; z < eventJson["td_event"][j]["paramKeyList"].length; z++) {
                                if (z != 0)
                                    td_onclick += ",";
                                td_onclick += "'" + VectorData[i][eventJson["td_event"][j]["paramKeyList"][z]["paramKey"]] + "'";
                            }
                            td_onclick += ")\"";
                        }
                        tbody_str += "<button type=\"button\" class=\"btn btn-primary btn-xs\" " + td_onclick + ">" + eventJson["td_event"][j]["eventName"] + "</button>";
                    }
                    tbody_str += "</td>"
                }
                tbody_str += "</tr>"
            }
        }
    }

    bm_html(thead_id, thead_str == "" ? "NoData" : thead_str);
    bm_html(tbody_id, tbody_str);

}
