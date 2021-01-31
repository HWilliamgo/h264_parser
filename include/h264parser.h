//
// Created by HWilliam on 2021/1/28.
//

#ifndef H264_PARSER_H264PARSER_H
#define H264_PARSER_H264PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Analysis H.264 Bitstream
 * @param url    Location of input H.264 bitstream file.
 */
int simplest_h264_parser(char *url,const FILE *out);

#ifdef __cplusplus
}
#endif

#endif //H264_PARSER_H264PARSER_H

