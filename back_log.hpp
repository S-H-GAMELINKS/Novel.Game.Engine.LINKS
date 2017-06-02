#ifndef LINKS_BACK_LOG_HPP_
#define LINKS_BACK_LOG_HPP_

//バックログ変数
extern char *BACKLOG_DELETE;

void BACKLOG_DRAW();
void BACKLOG_GET();
void incrementBackLogCount() noexcept;

#endif
