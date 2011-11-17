<?php

namespace ADOdb\Type;

/**
 * The String class class is used to enforce strong typing of the string type
 *
 * @author Nijikokun <nijikokun@shortmail.com> (main)
 * @author Dario <dario@ewide.eu> (adodb)
 * @copyright AOL <http://aol.nexua.org>
 * @package ADOdb\String
 */
class String {
    protected $_str;
    protected $_length;

    public function __construct($str = "") {
        $this->_str = $str;
        $this->_length = strlen($str);
    }

    /**
     * Verifies the emptiness of our current String.
     */
    public function isEmpty() {
        return $this->_length == 0 || $this->_str == "" || $this->_str == null;
    }

    /**
     * Returns our current String length
     */
    public function length() {
        return $this->_length;
    }

    /**
     * Converts an indice to the given character at the point.
     *
     * @todo Create Char Object.
     * @return Char
     */
    public function charAt($index) {
        if (($index < 0) || ($index >= $this->_length))
            throw new InvalidArgumentException("Index out of bounds.");

        return $this->_str[$index];
    }

    /**
     * Converts all characters in the current String
     * to their ord counterparts and returns in array form.
     *
     * @return Array
     */
    public function getBytes() {
        $bytes = array();

        for ($i = 0; $i < $this->_length; $i++){
             $bytes[] = ord($this->_str[$i]);
        }

        return $bytes;
    }

    /**
     * Tells whether the sequence of characters in our current String
     * matches the sequence in another.
     *
     * @param $another String to be checked upon.
     * @return Boolean
     */
    public function equals($another) {
        if ($this->_str == $another)
            return true;

        if ($this->_length == strlen($another)) {
            for ($i = 0; $i < strlen($this->_str); $i++)
                if ($this->_str[$i] != $another[$i])
                    return false;

            return true;
        }

        return false;
    }

    /**
     * Tells whether the sequence of characters in our current String
     * matches the sequence in another without case sensitivity.
     *
     * @param $another String to be checked upon.
     * @return Boolean
     */
    public function equalsIgnoreCase($another) {
        if ($this->equals($another))
            return true;

        if ($this->toLowerCase() == strtolower($another))
            return true;

        if ($this->_length == strlen($another)) {
            for ($i = 0; $i < strlen($this->_str); $i++)
                if (strtolower($this->_str[$i]) != strtolower($another[$i]))
                    return false;

            return true;
        }

        return false;
    }

    /**
     * Lexigraphically compares two strings and returns the numeric value.
     * This is UTF-8/16 Based. Beware of usage.
     *
     * @todo Create Integer Object
     * @param $another String to be checked upon.
     * @return Integer
     */
    public function compareTo($another) {
        $l1 = mb_strlen($this->_str);
        $l2 = mb_strlen($another);

        $i = 0;
        while ($i < $l1 && $i < $l2) {
            $c1 = mb_convert_encoding(mb_substr($this->_str, $i, 1),'utf-16le');
            $c1 = ord($c1[0]) + (ord($c1[1]) << 8);
            $c2 = mb_convert_encoding(mb_substr($another, $i, 1),'utf-16le');
            $c2 = ord($c2[0]) + (ord($c2[1]) << 8);
            $res = $c1 - $c2;

            if ($res != 0)
                return $res;

            $i++;
        }

        return $l1 - $l2;
    }

    /**
     * Converts all characters in the current String to lowercase.
     *
     * @return string
     */
    public function toLowerCase() {
        return new String(strtolower($this->_str));
    }

    /**
     * Converts all characters in the current String to uppercase.
     *
     * @return string
     */
    public function toUpperCase() {
        return new String(strtoupper($this->_str));
    }

    /**
     * Returns a new String containing the character array
     * from the given indices.
     *
     * @param $a Beginning index
     * @param $b Ending index
     * @return string
     */
    public function substring($a = "", $b = "") {
        if ($a == "" && $b == "")
            throw new InvalidArgumentException("Invalid start and end.");

        if (!is_int($a) && !is_int($b))
            throw new InvalidArgumentException("Start and end must be numeric.");

        if (is_int($a))
            return new String(substr($this->_str, $a));

        if (is_int($a) && is_int($b))
            return new String(substr($this->_str, $a, $b));

        throw new InvalidArgumentException("Invalid start and end.");
    }

    /**
     * Tells whether or not the current String contains
     * a given needle.
     *
     */
    public function contains($needle) {
        return (bool) strpos($this->_str, $needle) !== false;
    }

    /**
     * Tells whether or not the current String begins
     * with the string given.
     *
     * @param $needle String to be compared to.
     * @param $case Boolean that toggles case sensitivity.
     * @return Boolean
     */
    public function startsWith($needle, $case = true) {
        if ($case)
            return (strcmp(substr($this->_str, 0, strlen($needle)), $needle) === 0);

        return (strcasecmp(substr($this->_str, 0, strlen($needle)), $needle) === 0);
    }

    /**
     * Tells whether or not the current String begins
     * with the string given.
     *
     * @param $needle String to be compared to.
     * @param $case Boolean that toggles case sensitivity.
     * @return Boolean
     */
    public function endsWith($needle, $case = true) {
        if ($case)
            return (strcmp(substr($this->_str, strlen($this->_str) - strlen($needle)), $needle) === 0);

        return (strcasecmp(substr($this->_str, strlen($this->_str) - strlen($needle)), $needle) === 0);
    }

    /**
     * Returns the index within this string of the first occurrence of the
     * specified substring, starting at the specified index. If the substring
     * is not found, false is returned.
     *
     * @param $needle Substring to be searched for.
     * @param $starting Starting index, default 0.
     * @return False or Position
     */
    public function indexOf($needle, $starting = 0, $case = true) {
        if ($starting != 0)
            $pos = ($case) ? strpos($this->_str, $needle, $starting) : stripos($this->_str, $needle, $starting);
        else
            $pos = ($case) ? strpos($this->_str, $needle) : stripos($this->_str, $needle);

        if ($pos === false)
            return false;

        return $pos;
    }

    /**
     * Returns the index within this string of the last occurrence of the
     * specified substring, starting rightmost at the specified index.
     * If the substring is not found, false is returned.
     *
     * @param $needle Substring to be searched for.
     * @param $starting Starting index, default 0.
     * @return False or Position
     */
    public function lastIndexOf($needle, $starting = 0, $case = true) {
        if ($starting != 0)
            $pos = ($case) ? strrpos($this->_str, $needle, $starting) : strripos($this->_str, $needle, $starting);
        else
            $pos = ($case) ? strrpos($this->_str, $needle) : strripos($this->_str, $needle);

        if ($pos === false)
            return false;

        return $pos;
    }

    /**
     * Concatenates the specified string to the end of this string.
     *
     * @param $str the <code>String</code> that is concatenated to the end of this <code>String</code>.
     * @return String with the new section concatenated.
     */
    public function concat($str) {
        return new String($this->_str . $str);
    }

    /**
     * Replaces one string with another in the current String.
     *
     * @param $old Old character array (String).
     * @param $new New character array (String).
     */
    public function replace($old, $new) {
        return new String(str_replace($this->_str, $old, $new));
    }

    /**
     * Converts a string based on the string delimiter into an array of strings, each a substring of the string.
     *
     * @param $needle String delimiter
     */
    public function split($needle) {
        $result = explode($this->_str, $needle);
        return array_walk(
            $result,
            function(&$str) {
                $str = new String($str);
            }
        );
    }

    /**
     * To keep with Java's internal coding, we issue our own toString().
     *
     * You can use ->toString() or (string)$variable;
     * Either works fine.
     *
     * @return string
     */
    public function toString() {
        return $this->__toString();
    }

    /**
     * Magic internals to return string upon casting.
     *
     * @return string
     */
    public function __toString() {
        return $this->_str;
    }
}